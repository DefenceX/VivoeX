project(widget-tester)

include(FindPkgConfig)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(CAIRO REQUIRED cairo)
find_package(Protobuf REQUIRED)

set(SOURCE_FILES widget-tester.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/renderer_gva.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/renderer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/renderer_cairo.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/config_reader.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/events_gva.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/hmi_gva_helpers.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/widgets/widget.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/widgets/compass.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/widgets/keyboard.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/widgets/driver/speedometer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/widgets/driver/rpm_fuel.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/widgets/alarm_indicator.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/widgets/top_labels.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/widgets/bottom_labels.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/widgets/table/table.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/widgets/table/row_type.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/widgets/table/cell_type.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/widgets/side_labels.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/widgets/mode.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/gva_functions_common.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/log_gva.cc
    ${PROTO_SRCS}
)

include_directories(
    ${CMAKE_BINARY_DIR}/external/libnmea/src/include
    ${CMAKE_BINARY_DIR}/external/install/usr/local/include/
    ${CMAKE_BINARY_DIR}/external/libnmea/build/src
)

link_directories(${CMAKE_BINARY_DIR}/external/libnmea/build/src)

# OSMScout
include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/src/libosmscout/include)
include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/src/libosmscout-map/include)
include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/src/libosmscout-map-cairo/include)
link_directories(${CMAKE_BINARY_DIR}/external/libosmscout/build/libosmscout-map-cairo)
link_directories(${CMAKE_BINARY_DIR}/external/libosmscout/build/libosmscout)
link_directories(${CMAKE_BINARY_DIR}/external/libosmscout/build/libosmscout-map)
link_libraries(-lstdc++fs)

add_executable(widget-tester ${SOURCE_FILES})

target_link_libraries(widget-tester nmealib config-proto ${CAIRO_LIBRARIES} ${GTK3_LIBRARIES} )
target_include_directories(widget-tester PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR}/hmi-display/config ${CMAKE_CURRENT_SOURCE_DIR}/../hmi-display${CAIRO_INCLUDE_DIRS} ${PANGO_INCLUDE_DIRS} ${GTK3_INCLUDE_DIRS})
target_compile_options(widget-tester PUBLIC ${CAIRO_CFLAGS_OTHER} ${GTK3_CFLAGS_OTHER})
set_target_properties(widget-tester PROPERTIES UNITY_BUILD ON)

add_dependencies(widget-tester geographiclib libnmea config-proto)

