include(ExternalProject)

message (STATUS "Added libprotobuf to external submodules")

# ------------------------------------------------------------------------------
# libprotobuf
# ------------------------------------------------------------------------------
ExternalProject_Add(
    libprotobuf
    GIT_REPOSITORY      https://github.com/protocolbuffers/protobuf
    GIT_SHALLOW         1
    CMAKE_ARGS          -DCMAKE_INSTALL_MESSAGE=LAZY -DCMAKE_UNITY_BUILD=NO -Dprotobuf_BUILD_TESTS=OFF 
    GIT_TAG             v21.12
    PREFIX              ${CMAKE_BINARY_DIR}/external/libprotobuf/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/libprotobuf/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/libprotobuf/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/libprotobuf/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/libprotobuf/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/libprotobuf/build
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)

set(PROTOBUF_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/external/install/usr/local/include/)
set(PROTOBUF_LIBRARY protobuf)

if(MSYS)
  set(PROTOC "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/protobuf/bin/protoc.exe")
  set(PROTOBUF_LIBRARY_DIR "${CMAKE_BINARY_DIR}external/install/Program Files (x86)/protobuf/lib")
  set(PROTOBUF_INCLUDE_DIRS "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/protobuf/include")
else()
  set(PROTOC ${CMAKE_BINARY_DIR}/external/install/usr/local/bin/protoc)
  set(PROTOBUF_LIBRARY_DIR 
    ${CMAKE_BINARY_DIR}/external/install/usr/lib 
    ${CMAKE_BINARY_DIR}/external/install/usr/local/lib64
    ${CMAKE_BINARY_DIR}/external/install/usr/lib64
  )
endif()
