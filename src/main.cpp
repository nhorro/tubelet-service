#include <iostream>
#include <memory>
#include <string>
#include <boost/format.hpp>
#include <grpc++/grpc++.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

#include "tubelets.h"

/* -- Service */
#include "tubelet_service.grpc.pb.h"

const int VERSION_MAJOR = 1;
const int VERSION_MINOR = 1;
const int VERSION_REVISION = 1;

#define DEFAULT_WINDOW_WIDTH 320
#define DEFAULT_WINDOW_HEIGHT 200

class tubelet_service_impl final: public tubelet_service::tubelet_service::Service
{
public:
	tubelet_service_impl():
		tubs(0,0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT)
	{

	}

	grpc::Status get_version(::grpc::ServerContext* context, const ::tubelet_service::Empty* request, ::tubelet_service::get_version_response* response) override
	{
		std::cout << "Received get version" << std::endl;
		response->set_version(
				(boost::format("%d.%d.%d") % VERSION_MAJOR % VERSION_MINOR % VERSION_REVISION).str() );
		return Status::OK;
	}

	grpc::Status add_observation2d(::grpc::ServerContext* context, const ::tubelet_service::add_observation2d_request* request, ::tubelet_service::Empty* response) override
	{
		std::cout << "Received get add_observation2d" << std::endl;
		std::cout << "x: " << request->pos().x() << std::endl;
		std::cout << "y: " << request->pos().y() << std::endl;
		std::cout << "obs: { ci:" << request->obs().class_index()
				  << ", prob: " <<  request->obs().prob() << std::endl;
		return Status::OK;
	}

	grpc::Status get_all_tubelets2d(::grpc::ServerContext* context, const ::tubelet_service::Empty* request, ::tubelet_service::get_all_tubelets2d_response* response) override
	{
		for(double i=0.0;i<10.0;i++)
		{
			auto tub = response->mutable_tubelets()->Add();
			tub->mutable_pos()->set_x(1.0+1.0*i);
			tub->mutable_pos()->set_y(1.0+2.0*i);

			for(double j=0.0;j<5.0;j++)
			{
				auto obs = tub->mutable_observations()->Add();
				obs->set_class_index((int)j);
				obs->set_prob(i*j*0.01);
			}
		}
		return Status::OK;
	}

	grpc::Status clear(::grpc::ServerContext* context, const ::tubelet_service::Empty* request, ::tubelet_service::Empty* response) override
	{
		//TODO
		return Status::OK;
	}

	grpc::Status move_window(::grpc::ServerContext* context, const ::tubelet_service::move_window_request* request, ::tubelet_service::Empty* response) override
	{
		//TODO
		return Status::OK;
	}
private:
	tubelets tubs;
};


void run_server(int port=50051)
{
  std::string server_address( "0.0.0.0:"+std::to_string(port));

  tubelet_service_impl service;
  ServerBuilder builder;

  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char** argv)
{
	run_server();
	return 0;
}
