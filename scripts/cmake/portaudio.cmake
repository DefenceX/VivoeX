
include(ExternalProject)

message (STATUS "Added portaudio to external submodules")

# ------------------------------------------------------------------------------
# portaudio
# ------------------------------------------------------------------------------
if (MSYS)
    ExternalProject_Add(
        portaudio
        GIT_REPOSITORY      https://github.com/PortAudio/portaudio
        GIT_SHALLOW         1
        GIT_TAG             v19.7.0
        CMAKE_ARGS          -DCMAKE_INSTALL_MESSAGE=LAZY  -DCMAKE_BUILD_TYPE=Release -DPA_USE_DS=1 -DPA_USE_WDMKS=1 -DPA_USE_WDMKS_DEVICE_INFO=1 -DPA_USE_WMME=1 -DPA_USE_WASAPI=1
        PREFIX              ${CMAKE_BINARY_DIR}/external/portaudio/prefix
        TMP_DIR             ${CMAKE_BINARY_DIR}/external/portaudio/tmp
        STAMP_DIR           ${CMAKE_BINARY_DIR}/external/portaudio/stamp
        DOWNLOAD_DIR        ${CMAKE_BINARY_DIR}/external/portaudio/download
        SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/portaudio/src
        BINARY_DIR          ${CMAKE_BINARY_DIR}/external/portaudio/build
        INSTALL_COMMAND     make DESTDIR=${CMAKE_BINARY_DIR}/external/install install 
        UPDATE_DISCONNECTED 1
    )
    add_dependencies(portaudio libsndfile)
    set(PORTAUDIO_INCLUDE_DIR 
        ${CMAKE_BINARY_DIR}/external/install/mingw64/include
        "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/portaudio/include")
    set(PORTAUDIO_LIBRARY_DIR
        "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/portaudio/lib")
    set(PORTAUDIO_LIBRARIES portaudio.a)
else()
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
    add_dependencies(portaudio libsndfile alsa)
    set(PORTAUDIO_INCLUDE_DIR ${CMAKE_BINARY_DIR}/external/install/usr/local/include)
    set(PORTAUDIO_LIBRARIES asound portaudio.a)
endif()
