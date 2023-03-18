
include(ExternalProject)

message (STATUS "Added portaudio to external submodules")

# ------------------------------------------------------------------------------
# portaudio
# ------------------------------------------------------------------------------
ExternalProject_Add(
    portaudio
    GIT_REPOSITORY      https://github.com/PortAudio/portaudio
    GIT_SHALLOW         1
    GIT_TAG             v19.7.0
    CMAKE_ARGS          -DCMAKE_INSTALL_MESSAGE=LAZY -DCMAKE_INSTALL_LIBDIR=${CMAKE_INSTALL_LIBDIR} -DGFLAGS_USE_TARGET_NAMESPACE=ON -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} -DCMAKE_CXX_FLAGS="-fPIC"
    PREFIX              ${CMAKE_BINARY_DIR}/external/portaudio/prefix
    TMP_DIR             ${CMAKE_BINARY_DIR}/external/portaudio/tmp
    STAMP_DIR           ${CMAKE_BINARY_DIR}/external/portaudio/stamp
    DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/portaudio/download
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/portaudio/src
    BUILD_IN_SOURCE     TRUE
    CONFIGURE_COMMAND   ./configure --enable-cxx --enable-static
    INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install 
    UPDATE_DISCONNECTED 1
)

add_dependencies(portaudio libsndfile)