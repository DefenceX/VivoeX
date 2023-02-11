project(config-proto)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_BINARY_DIR}/external/install/usr/local/include)

add_custom_command(
  OUTPUT ${CMAKE_BINARY_DIR}/hmi-display/config/config.pb.cc
  COMMAND ${PROTOC} --cpp_out ${CMAKE_BINARY_DIR}/hmi-display/config -I ${CMAKE_SOURCE_DIR}/vivoe-lite/hmi-display/config ${CMAKE_SOURCE_DIR}/hmi-display/config/config.proto --proto_path ${CMAKE_SOURCE_DIR}/hmi-display/config
  )

set(PROTO_SRCS ${CMAKE_BINARY_DIR}/hmi-display/config/config.pb.cc)

add_library(config-proto STATIC ${PROTO_SRCS})
target_link_libraries(config-proto ${PROTOBUF_LIBRARY})

add_dependencies(config-proto libprotobuf)