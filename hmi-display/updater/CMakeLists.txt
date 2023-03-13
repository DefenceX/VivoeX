
project(hmi-updater)

set(SOURCES 
    updater.cc   
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
add_library(hmi-updater STATIC ${SOURCES})