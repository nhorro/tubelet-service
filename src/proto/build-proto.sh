# C++
protoc -I . --grpc_out=.. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` tubelet_service.proto
protoc -I . --cpp_out=.. tubelet_service.proto

# Python
python -m grpc_tools.protoc -I . --python_out=../../python --grpc_python_out=../../python tubelet_service.proto