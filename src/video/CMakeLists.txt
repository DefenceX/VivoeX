project(hmi-video)

add_library(hmi-video src/gva_video.cc src/gva_video_rtp_yuv.cc)
add_dependencies(hmi-video libglog vivoe_media)
target_include_directories(hmi-video PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/src
    ${CMAKE_BINARY_DIR}/external/install/usr/local/include
)