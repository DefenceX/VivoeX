include(FindPkgConfig)
project(widgets)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/alarm_indicator.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/bottom_labels.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/rpm_fuel.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/driver/speedometer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/keyboard.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/mode.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/plan_position_indicator.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/side_labels.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/table/cell_type.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/table/row_type.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/table/table.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/table/table_dynamic.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/top_labels.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/widget.cc
)

add_library(widgets STATIC ${SOURCES})
include_directories(widgets BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/hmi-display)
target_link_libraries (widgets config-proto ${PROTOBUF_LIBRARY} ${GTK_LIBRARIES3})
target_include_directories(widgets BEFORE PRIVATE ${PROTOBUF_INCLUDE_DIRS} ${GLOG_INCLUDE_DIRS})

target_include_directories(widgets BEFORE PUBLIC ${GTK3_INCLUDE_DIRS} ${CMAKE_BINARY_DIR}/hmi-display/config ${CMAKE_BINARY_DIR}/external/libprotobuf/build)
add_dependencies(widgets libglog config-proto)




