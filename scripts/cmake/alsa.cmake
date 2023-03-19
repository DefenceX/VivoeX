if (NOT MSYS)
include(ExternalProject)

message (STATUS "Added alsa to external submodules")

# ------------------------------------------------------------------------------
# alsa
# ------------------------------------------------------------------------------
ExternalProject_Add(
    alsa
    GIT_REPOSITORY      https://github.com/alsa-project/alsa-lib
    GIT_SHALLOW         1
    GIT_TAG             v1.2.8
    CMAKE_ARGS          -DCMAKE_INSTALL_MESSAGE=LAZY -DCMAKE_INSTALL_LIBDIR=${CMAKE_INSTALL_LIBDIR} -DGFLAGS_USE_TARGET_NAMESPACE=ON -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} -DCMAKE_CXX_FLAGS="-fPIC"
    PREFIX              ${CMAKE_BINARY_DIR}/external/alsa/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/alsa/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/alsa/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/alsa/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/alsa/src
    BUILD_IN_SOURCE     TRUE
    CONFIGURE_COMMAND   libtoolize --force --copy --automake && aclocal && autoheader && automake --foreign --copy --add-missing && autoconf && ./configure --disable-aload --disable-mixer --disable-rawmidi --disable-hwdep --disable-seq --disable-ucm --disable-topology --disable-maintainer-mode --disable-python --disable-old-symbols 
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install 
    UPDATE_DISCONNECTED 1
)
endif()
