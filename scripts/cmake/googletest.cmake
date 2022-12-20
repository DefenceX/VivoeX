# ------------------------------------------------------------------------------
# googletest
# ------------------------------------------------------------------------------
ExternalProject_Add(
    googletest
    GIT_REPOSITORY      https://github.com/google/googletest
    GIT_TAG             v1.12.0
    GIT_SHALLOW         5
    CMAKE_ARGS          -DCMAKE_UNITY_BUILD=NO
    PREFIX              ${CMAKE_BINARY_DIR}/external/googletest/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/googletest/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/googletest/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/googletest/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/googletest/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/googletest/build
    BUILD_COMMAND       make $(nproc)
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)

set(GTEST_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/external/install/usr/local/include)
set(GTEST_LIBARAIES gmock_main gmock gtest pthread)
# Ubuntu=/usr/local/lib CentOS=/usr/local/lib64 UbuntuArm=/usr/local/lib/aarch64-linux-gnu, we just set paths for both
set(GTEST_LIBRARY_DIRS ${CMAKE_BINARY_DIR}/external/install/usr/local/lib ${CMAKE_BINARY_DIR}/external/install/usr/local/lib64 ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/aarch64-linux-gnu)