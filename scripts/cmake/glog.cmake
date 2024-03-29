
include(ExternalProject)

message (STATUS "Added libglog to external submodules")

if (MSYS)
  set(GFLAGS_DIR "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/gflags/${CMAKE_INSTALL_LIBDIR}")
else()
  set(GFLAGS_DIR ${CMAKE_BINARY_DIR}/external/install/usr/local/${CMAKE_INSTALL_LIBDIR}/cmake/gflags)
endif()

# ------------------------------------------------------------------------------
# libglog
# ------------------------------------------------------------------------------
ExternalProject_Add(
    libglog
    GIT_REPOSITORY      https://github.com/google/glog
    GIT_SHALLOW         1
    CMAKE_ARGS          -DCMAKE_INSTALL_LIBDIR=/usr/${CMAKE_INSTALL_LIBDIR} -Dgflags_DIR=${GFLAGS_DIR} -DCMAKE_INSTALL_LIBDIR=${CMAKE_INSTALL_LIBDIR} -DGFLAGS_USE_TARGET_NAMESPACE=ON -DCMAKE_CXX_FLAGS="-fPIC" -DCMAKE_INSTALL_MESSAGE=LAZY -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    GIT_TAG             v0.6.0
    PREFIX              ${CMAKE_BINARY_DIR}/external/libglog/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/libglog/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/libglog/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/libglog/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/libglog/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/libglog/build
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install 
    UPDATE_DISCONNECTED 1
    DEPENDS             libgflags 
)

set(GLOG_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/external/install/usr/local/include)
set(GLOG_LIBRARY glog)

if(MSYS)
  set(GLOG_LIBRARY_DIR "${CMAKE_BINARY_DIR}external/install/Program Files (x86)/glog/${CMAKE_INSTALL_LIBDIR}")
else()
  set(GLOG_LIBRARY_DIR 
    ${CMAKE_BINARY_DIR}/external/install/usr/lib 
    ${CMAKE_BINARY_DIR}/external/install/usr/lib64
    ${CMAKE_BINARY_DIR}/external/install/usr/local/lib64
    ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/aarch64-linux-gnu
  )     
endif()
