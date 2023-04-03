
project(hmi-updater)

set(SOURCES 
    updater.cc   
)

add_library(hmi-updater STATIC ${SOURCES})
target_include_directories(hmi-updater BEFORE PRIVATE
     /usr/include/cairo
    ${GTK3_INCLUDE_DIRS}
    ${PROTOBUF_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/.. 
    ${CMAKE_BINARY_DIR}/hmi-display/config
    ${PORTAUDIO_INCLUDE_DIR}
    ${SNDFILE_LIBRARY_DIR}
)

add_dependencies(hmi-updater portaudio config-proto libglog)