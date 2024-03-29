# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
import grpc

import tubelet_service_pb2 as tubelet__service__pb2


class tubelet_serviceStub(object):
  # missing associated documentation comment in .proto file
  pass

  def __init__(self, channel):
    """Constructor.

    Args:
      channel: A grpc.Channel.
    """
    self.get_version = channel.unary_unary(
        '/tubelet_service.tubelet_service/get_version',
        request_serializer=tubelet__service__pb2.Empty.SerializeToString,
        response_deserializer=tubelet__service__pb2.get_version_response.FromString,
        )
    self.add_observation2d = channel.unary_unary(
        '/tubelet_service.tubelet_service/add_observation2d',
        request_serializer=tubelet__service__pb2.add_observation2d_request.SerializeToString,
        response_deserializer=tubelet__service__pb2.Empty.FromString,
        )
    self.get_all_tubelets2d = channel.unary_unary(
        '/tubelet_service.tubelet_service/get_all_tubelets2d',
        request_serializer=tubelet__service__pb2.Empty.SerializeToString,
        response_deserializer=tubelet__service__pb2.get_all_tubelets2d_response.FromString,
        )
    self.reset = channel.unary_unary(
        '/tubelet_service.tubelet_service/reset',
        request_serializer=tubelet__service__pb2.Empty.SerializeToString,
        response_deserializer=tubelet__service__pb2.Empty.FromString,
        )
    self.clip = channel.unary_unary(
        '/tubelet_service.tubelet_service/clip',
        request_serializer=tubelet__service__pb2.Empty.SerializeToString,
        response_deserializer=tubelet__service__pb2.Empty.FromString,
        )
    self.move_window = channel.unary_unary(
        '/tubelet_service.tubelet_service/move_window',
        request_serializer=tubelet__service__pb2.move_window_request.SerializeToString,
        response_deserializer=tubelet__service__pb2.Empty.FromString,
        )
    self.set_window_position = channel.unary_unary(
        '/tubelet_service.tubelet_service/set_window_position',
        request_serializer=tubelet__service__pb2.set_window_position_request.SerializeToString,
        response_deserializer=tubelet__service__pb2.Empty.FromString,
        )


class tubelet_serviceServicer(object):
  # missing associated documentation comment in .proto file
  pass

  def get_version(self, request, context):
    # missing associated documentation comment in .proto file
    pass
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def add_observation2d(self, request, context):
    # missing associated documentation comment in .proto file
    pass
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def get_all_tubelets2d(self, request, context):
    # missing associated documentation comment in .proto file
    pass
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def reset(self, request, context):
    # missing associated documentation comment in .proto file
    pass
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def clip(self, request, context):
    # missing associated documentation comment in .proto file
    pass
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def move_window(self, request, context):
    # missing associated documentation comment in .proto file
    pass
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')

  def set_window_position(self, request, context):
    # missing associated documentation comment in .proto file
    pass
    context.set_code(grpc.StatusCode.UNIMPLEMENTED)
    context.set_details('Method not implemented!')
    raise NotImplementedError('Method not implemented!')


def add_tubelet_serviceServicer_to_server(servicer, server):
  rpc_method_handlers = {
      'get_version': grpc.unary_unary_rpc_method_handler(
          servicer.get_version,
          request_deserializer=tubelet__service__pb2.Empty.FromString,
          response_serializer=tubelet__service__pb2.get_version_response.SerializeToString,
      ),
      'add_observation2d': grpc.unary_unary_rpc_method_handler(
          servicer.add_observation2d,
          request_deserializer=tubelet__service__pb2.add_observation2d_request.FromString,
          response_serializer=tubelet__service__pb2.Empty.SerializeToString,
      ),
      'get_all_tubelets2d': grpc.unary_unary_rpc_method_handler(
          servicer.get_all_tubelets2d,
          request_deserializer=tubelet__service__pb2.Empty.FromString,
          response_serializer=tubelet__service__pb2.get_all_tubelets2d_response.SerializeToString,
      ),
      'reset': grpc.unary_unary_rpc_method_handler(
          servicer.reset,
          request_deserializer=tubelet__service__pb2.Empty.FromString,
          response_serializer=tubelet__service__pb2.Empty.SerializeToString,
      ),
      'clip': grpc.unary_unary_rpc_method_handler(
          servicer.clip,
          request_deserializer=tubelet__service__pb2.Empty.FromString,
          response_serializer=tubelet__service__pb2.Empty.SerializeToString,
      ),
      'move_window': grpc.unary_unary_rpc_method_handler(
          servicer.move_window,
          request_deserializer=tubelet__service__pb2.move_window_request.FromString,
          response_serializer=tubelet__service__pb2.Empty.SerializeToString,
      ),
      'set_window_position': grpc.unary_unary_rpc_method_handler(
          servicer.set_window_position,
          request_deserializer=tubelet__service__pb2.set_window_position_request.FromString,
          response_serializer=tubelet__service__pb2.Empty.SerializeToString,
      ),
  }
  generic_handler = grpc.method_handlers_generic_handler(
      'tubelet_service.tubelet_service', rpc_method_handlers)
  server.add_generic_rpc_handlers((generic_handler,))
