message (STATUS "Added libsndfile to external submodules")

# ------------------------------------------------------------------------------
# libsndfile
# ------------------------------------------------------------------------------
ExternalProject_Add(
    libsndfile
    GIT_REPOSITORY      https://github.com/libsndfile/libsndfile
    GIT_SHALLOW         1
    GIT_TAG             1.2.0
    CMAKE_ARGS          -DCMAKE_INSTALL_MESSAGE=LAZY -DCMAKE_INSTALL_LIBDIR=${CMAKE_INSTALL_LIBDIR} -DGFLAGS_USE_TARGET_NAMESPACE=ON -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} -DCMAKE_CXX_FLAGS="-fPIC"
    PREFIX              ${CMAKE_BINARY_DIR}/external/libsndfile/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/libsndfile/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/libsndfile/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/libsndfile/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/libsndfile/src
    BUILD_IN_SOURCE     TRUE
    CONFIGURE_COMMAND   autoreconf -vif && ./configure 
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install 
    UPDATE_DISCONNECTED 1
)
