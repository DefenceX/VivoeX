project(config-proto)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_BINARY_DIR}/external/install/usr/local/include)

add_custom_command(
  OUTPUT ${CMAKE_BINARY_DIR}/src/config/config.pb.cc
  COMMAND ${PROTOC} --cpp_out ${CMAKE_BINARY_DIR}/src/config -I ${CMAKE_SOURCE_DIR}/vivoe-lite/src/config ${CMAKE_SOURCE_DIR}/src/config/config.proto --proto_path ${CMAKE_SOURCE_DIR}/src/config
  DEPENDS ${CMAKE_SOURCE_DIR}/src/config/config.proto
  )

set(PROTO_SRCS ${CMAKE_BINARY_DIR}/src/config/config.pb.cc)

add_library(config-proto STATIC ${PROTO_SRCS})
# target_link_directories(config-proto BEFORE PRIVATE ${PROTOBUF_LIBRARY_DIR})
# target_link_libraries(config-proto  ${PROTOBUF_LIBRARY})
# target_include_directories(config-proto BEFORE PRIVATE ${PROTOBUF_INCLUDE_DIR})

add_dependencies(config-proto libprotobuf)