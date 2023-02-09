
include(ExternalProject)

message (STATUS "Added libglog to external submodules")

# ------------------------------------------------------------------------------
# libglog
# ------------------------------------------------------------------------------
ExternalProject_Add(
    libglog
    GIT_REPOSITORY      https://github.com/google/glog
    GIT_SHALLOW         1
    CMAKE_ARGS          -Dgflags_DIR=${CMAKE_BINARY_DIR}/external/install/usr/local/lib/cmake/gflags -DCMAKE_CXX_FLAGS="-fPIC" -DCMAKE_INSTALL_MESSAGE=LAZY -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    GIT_TAG             v0.6.0  
    PREFIX              ${CMAKE_BINARY_DIR}/external/libglog/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/libglog/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/libglog/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/libglog/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/libglog/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/libglog/build
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install 
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)

add_dependencies(libglog libgflags googletest)