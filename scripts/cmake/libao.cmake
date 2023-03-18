include(ExternalProject)

message (STATUS "Added libao to external submodules")

# ------------------------------------------------------------------------------
# libao
# ------------------------------------------------------------------------------
ExternalProject_Add(
    libao
    GIT_REPOSITORY      https://github.com/xiph/libao
    GIT_SHALLOW         1
    GIT_TAG             1.2.2
    CMAKE_ARGS          -DCMAKE_INSTALL_MESSAGE=LAZY -DCMAKE_INSTALL_LIBDIR=${CMAKE_INSTALL_LIBDIR} -DGFLAGS_USE_TARGET_NAMESPACE=ON -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} -DCMAKE_CXX_FLAGS="-fPIC"
    PREFIX              ${CMAKE_BINARY_DIR}/external/libao/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/libao/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/libao/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/libao/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/libao/src
    BUILD_IN_SOURCE     TRUE
    CONFIGURE_COMMAND   ./autogen.sh && ./configure 
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install 
    UPDATE_DISCONNECTED 1
)

add_dependencies(libao libsndfile)