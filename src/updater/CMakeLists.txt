
project(hmiupdater)

set(SOURCES 
    updater.cc   
)

add_library(hmiupdater STATIC ${SOURCES})
target_include_directories(hmiupdater BEFORE PRIVATE
     /usr/include/cairo
    ${GTK3_INCLUDE_DIRS}
    ${PROTOBUF_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/.. 
    ${CMAKE_BINARY_DIR}/src/config
    ${PORTAUDIO_INCLUDE_DIR}
    ${SNDFILE_LIBRARY_DIR}
)

add_dependencies(hmiupdater portaudio config-proto libglog)