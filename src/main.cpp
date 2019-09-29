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
		double clustering_dist = 3.0; //TODO: make parameter

		this->tubs.add_observation(
				request->pos().x(),
				request->pos().y(),
				request->obs().class_index(),
				request->obs().prob(),
				clustering_dist
		);

		return Status::OK;
	}

	grpc::Status get_all_tubelets2d(::grpc::ServerContext* context, const ::tubelet_service::Empty* request, ::tubelet_service::get_all_tubelets2d_response* response) override
	{
		auto tree = this->tubs.get_tree();
		for(auto const& v: tree)
		{
			auto new_tub = response->mutable_tubelets()->Add();
			new_tub->mutable_pos()->set_x(v.x );
			new_tub->mutable_pos()->set_y(v.y );

			// observations
			for(auto o: *(v.obs))
			{
				auto new_obs = new_tub->mutable_observations()->Add();
				new_obs->set_class_index(o.ci );
				new_obs->set_prob(o.prob);
			}
		}
		return Status::OK;
	}

	grpc::Status reset(::grpc::ServerContext* context, const ::tubelet_service::Empty* request, ::tubelet_service::Empty* response) override
	{
		this->tubs.clear();
		return Status::OK;
	}

	grpc::Status clip(::grpc::ServerContext* context, const ::tubelet_service::Empty* request, ::tubelet_service::Empty* response) override
	{
		this->tubs.clip();
		return Status::OK;
	}

	grpc::Status move_window(::grpc::ServerContext* context, const ::tubelet_service::move_window_request* request, ::tubelet_service::Empty* response) override
	{
		this->tubs.move_frustrum(request->dx(),request->dy());
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
