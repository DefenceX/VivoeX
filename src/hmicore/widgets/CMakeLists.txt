include(FindPkgConfig)
project(widgets)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/ai/object_localisation.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/alarm_indicator.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/bottom_labels.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/rpm_fuel.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/speedometer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/table/message_box.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/canvas/canvas.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/canvas/video.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/keyboard.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/mode.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/plan_position_indicator.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/side_labels.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/table/cell_type.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/table/row_type.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/table/table.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/table/table_dynamic.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/table/status_bar.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/top_labels.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/onscreen_bezel_btns.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/widget.cc
)

add_library(widgets STATIC ${SOURCES})
include_directories(widgets BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries (widgets config-proto ${PROTOBUF_LIBRARY} ${GTK_LIBRARIES3})
target_include_directories(widgets BEFORE PRIVATE ${PROTOBUF_INCLUDE_DIRS} ${GLOG_INCLUDE_DIRS} ${NMEA_INCLUDE_DIR} ${MEDIA_INCLUDE_DIR})

target_include_directories(widgets BEFORE PUBLIC ${GTK3_INCLUDE_DIRS} ${CMAKE_BINARY_DIR}/src/config ${CMAKE_BINARY_DIR}/external/libprotobuf/build)
add_dependencies(widgets libglog config-proto libmediax)




