
include(ExternalProject)

message (STATUS "Added libgflags to external submodules")

set(GFLAGS_USE_TARGET_NAMESPACE ON)

# ------------------------------------------------------------------------------
# libgflags
# ------------------------------------------------------------------------------
ExternalProject_Add(
    libgflags
    GIT_REPOSITORY      https://github.com/gflags/gflags
    GIT_SHALLOW         1
    GIT_TAG             v2.2.2 
    CMAKE_ARGS          -DCMAKE_INSTALL_MESSAGE=LAZY -DGFLAGS_USE_TARGET_NAMESPACE=ON -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} -DCMAKE_CXX_FLAGS="-fPIC" 
    PREFIX              ${CMAKE_BINARY_DIR}/external/libgflags/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/libgflags/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/libgflags/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/libgflags/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/libgflags/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/libgflags/build
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install 
    UPDATE_DISCONNECTED 0
    BUILD_ALWAYS        0
)

add_dependencies(libgflags googletest)