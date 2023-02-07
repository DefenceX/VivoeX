
if (${CMAKE_SYSTEM_NAME} MATCHES "MSYS")
message("libosmscout not currently supported under MSYS2...")
else()

include(ExternalProject)

message (STATUS "Added libosmscout to external submodules")

# ------------------------------------------------------------------------------
# libosmscout
# ------------------------------------------------------------------------------
set(OSMSCOUT_BUILD_TEST OFF CACHE BOOL "Disable build of test library")
list(APPEND CMAKE_MODULE_PATH ../libosmscout/cmake)

ExternalProject_Add(
    libosmscout
    GIT_REPOSITORY      https://github.com/Framstag/libosmscout
    GIT_TAG             1.1.0
    GIT_SHALLOW         1
    CMAKE_ARGS           -Wno-dev -DCMAKE_CXX_FLAGS='-lstdc++fs\ -std=c++11' -DCMAKE_UNITY_BUILD=YES -DCMAKE_BUILD_TYPE=Release -DOSMSCOUT_BUILD_DOC_API=Off -DOSMSCOUT_BUILD_TESTS=Off -DOSMSCOUT_BUILD_GPX=Off -DOSMSCOUT_BUILD_MAP_AGG=Off -DOSMSCOUT_BUILD_MAP_SVG=Off -DOSMSCOUT_BUILD_MAP_OPENGL=Off -DOSMSCOUT_BUILD_MAP_QT=Off -D=OSMSCOUT_BUILD_CLIENT_QT=Off -DOSMSCOUT_BUILD_MAP_SVG=Off -DOSMSCOUT_BUILD_WEBPAGE=Off
    PREFIX              ${CMAKE_BINARY_DIR}/external/libosmscout/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/libosmscout/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/libosmscout/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/libosmscout/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/libosmscout/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/libosmscout/build
    BUILD_COMMAND       make $(nprocs)
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install
    TEST_COMMAND        ""
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)
endif()

set(OSMSCOUT_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/external/install/usr/local/include)
set(OSMSCOUT_LIBARAIES osmscout_import osmscout_map_cairo osmscout_map osmscout)