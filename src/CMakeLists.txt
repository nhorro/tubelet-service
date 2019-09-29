cmake_minimum_required(VERSION 3.6)

# Boost
find_package(Boost 1.67)

# Protobuf
find_package(Protobuf REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")

# gRPC
find_package(gRPC REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

# gRPC C++ plugin
get_target_property(gRPC_CPP_PLUGIN_EXECUTABLE gRPC::grpc_cpp_plugin
    IMPORTED_LOCATION_RELEASE)


# Generate protobufs

# Proto file
get_filename_component(hw_proto "proto/tubelet_service.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

# Generated sources
protobuf_generate_cpp(hw_proto_srcs hw_proto_hdrs "${hw_proto}")
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/tubelet_service.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/tubelet_service.grpc.pb.h")
add_custom_command(
      OUTPUT "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
      COMMAND protobuf::protoc
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}" -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="${gRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hw_proto}"
      DEPENDS "${hw_proto}")

# Generated include directory
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# Target
add_executable( tubelet-service 
	main.cpp
	tubelets.cpp
	${hw_proto_srcs}
    ${hw_grpc_srcs}   
)

target_include_directories( tubelet-service
	PRIVATE
		${Boost_INCLUDE_DIRS}
)

target_link_libraries( tubelet-service 
	PRIVATE    	
		dl
        #Boost::program_options
	    #Boost::system
	    #Boost::regex
		#Boost::thread
		#Boost::system	
		gRPC::grpc++_unsecure
		protobuf::libprotobuf
		rt
)

install( TARGETS tubelet-service
		 RUNTIME DESTINATION bin )
  
