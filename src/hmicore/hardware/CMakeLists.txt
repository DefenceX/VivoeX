set(SOURCES audio.cc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../..)
add_library(hmiaudio ${SOURCES})
add_dependencies(hmiaudio portaudio libglog)
target_include_directories (hmiaudio PUBLIC
    ${PORTAUDIO_INCLUDE_DIR})