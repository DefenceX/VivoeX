project(config-proto)

if (${CMAKE_SYSTEM_NAME} MATCHES "MINGW64_NT-10.0-17763")
else()
	find_package(Protobuf REQUIRED)
	message(STATUS "Using Protocol Buffers ${Protobuf_VERSION}...")
	include_directories(${Protobuf_INCLUDE_DIRS})
	include_directories(${CMAKE_CURRENT_BINARY_DIR})
	protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS config.proto)
endif()

add_library(config-proto STATIC ${PROTO_SRCS})
target_link_libraries(config-proto ${Protobuf_LIBRARY} )