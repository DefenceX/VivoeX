
include(ExternalProject)

message (STATUS "Added libgflags to external submodules")

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
    UPDATE_DISCONNECTED 1
)

if (MSYS)
  set(GFLAGS_LIBS gflags_static)
else()
  set(GFLAGS_LIBS gflags)
endif()

add_dependencies(libgflags googletest)
