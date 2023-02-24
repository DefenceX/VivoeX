include(ExternalProject)

message (STATUS "Added googletest to external submodules")

# ------------------------------------------------------------------------------
# googletest
# ------------------------------------------------------------------------------
ExternalProject_Add(
    googletest
    GIT_REPOSITORY      https://github.com/google/googletest
    GIT_TAG             v1.13.0
    GIT_SHALLOW         5
    CMAKE_ARGS          -DCMAKE_UNITY_BUILD=NO -DCMAKE_INSTALL_LIBDIR=${CMAKE_INSTALL_LIBDIR}
    PREFIX              ${CMAKE_BINARY_DIR}/external/googletest/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/googletest/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/googletest/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/googletest/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/googletest/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/googletest/build
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install
    UPDATE_DISCONNECTED 1
)

if (MSYS)
  set(GTEST_LIBRARY_DIRS "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/googletest-distribution/${CMAKE_INSTALL_LIBDIR}")
else()
  set(GTEST_LIBRARY_DIRS
    GTEST_LIBRARY_DIRS ${CMAKE_BINARY_DIR}/external/install/usr/local/lib
    GTEST_LIBRARY_DIRS ${CMAKE_BINARY_DIR}/external/install/usr/local/lib64
    GTEST_LIBRARY_DIRS ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/aarch64-linux-gnu
  )
endif()
set(GTEST_LIBARAIES gmock_main gmock gtest pthread)
# Ubuntu=/usr/local/lib CentOS=/usr/local/lib64 UbuntuArm=/usr/local/lib/aarch64-linux-gnu, Windows Program Files, we just set paths for both
set(GTEST_INCLUDE_DIRS 
  ${CMAKE_BINARY_DIR}/external/install/usr/local/include
 "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/googletest-distribution/include")
