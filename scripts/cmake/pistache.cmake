project(pistache)

message (STATUS "Added pistache to external submodules")

# ------------------------------------------------------------------------------
# pistache
# ------------------------------------------------------------------------------
ExternalProject_Add(
    libpistache
    GIT_REPOSITORY      https://github.com/pistacheio/pistache
    GIT_SHALLOW         1
    CMAKE_ARGS          -DCMAKE_INSTALL_MESSAGE=LAZY -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} -Wno-dev
    GIT_TAG             0.0.5 
    PREFIX              ${CMAKE_BINARY_DIR}/external/libpistache/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/libpistache/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/libpistache/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/libpistache/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/libpistache/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/libpistache/build
    CONFIGURE_COMMAND   meson setup ${MESON_CROSS_COMPILER} ../src --buildtype=release -DPISTACHE_USE_SSL=false -DPISTACHE_BUILD_EXAMPLES=false -DPISTACHE_BUILD_TESTS=false -DPISTACHE_BUILD_DOCS=false 
    BUILD_COMMAND       meson compile -C ../build
    INSTALL_COMMAND     DESTDIR=${CMAKE_BINARY_DIR}/external/install  meson install -C ../build
    UPDATE_DISCONNECTED 1
    BUILD_ALWAYS        0
)

set(PISTACHE_INCLUDE_DIR ${CMAKE_BINARY_DIR}/external/install/usr/local/include/pistache ${CMAKE_BINARY_DIR}/external/libpistache/src/subprojects/rapidjson-1.1.0/include/)
set(PISTACHE_LIBRARY_DIR ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/x86_64-linux-gnu)