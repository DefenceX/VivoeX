project(widget-tester)

include(FindPkgConfig)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
# pkg_check_modules(CAIRO REQUIRED cairo)

set(SOURCE_FILES widget-tester.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/renderer_gva.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/renderer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/renderer_cairo.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/config_reader.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/events_gva.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/touch_gva.cc 
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
)

include_directories(
    ${CMAKE_BINARY_DIR}/external/libnmea/src/include
    ${CMAKE_BINARY_DIR}/external/install/usr/local/include/
    ${CMAKE_BINARY_DIR}/external/libnmea/build/src
)

link_directories(${CMAKE_BINARY_DIR}/external/libnmea/build/src)
link_directories(${CMAKE_BINARY_DIR}/external/install/usr/local/lib)
link_directories(${CMAKE_BINARY_DIR}/external/install/usr/lib64)

# OSMScout
include_directories(${CMAKE_SOURCE_DIR}/hmi-display)
link_libraries(-lstdc++fs)

add_executable(widget-tester ${SOURCE_FILES})
target_link_libraries(widget-tester glog nmea config-proto ${OSMSCOUT_LIBARAIES} ${CAIRO_LIBRARIES} ${GTK3_LIBRARIES} )
target_include_directories(widget-tester PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR}/hmi-display/config ${CMAKE_CURRENT_SOURCE_DIR}/../hmi-display ${OSMSCOUT_INCLUDE_DIRS} ${CAIRO_INCLUDE_DIRS} ${PANGO_INCLUDE_DIRS} ${GTK3_INCLUDE_DIRS})
target_compile_options(widget-tester PUBLIC ${CAIRO_CFLAGS_OTHER} ${GTK3_CFLAGS_OTHER})
set_target_properties(widget-tester PROPERTIES UNITY_BUILD ON)

if (MSYS)
# Static link libraries .a
target_link_directories(widget-tester BEFORE PRIVATE
"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/gflags/lib"
"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/glog/lib"
"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/protobuf/lib"
"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/libosmscout/lib"
"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/libosmscout/lib"
"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/nmea/lib"
"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/GeographicLib/lib"
)
endif()

add_dependencies(widget-tester libglog geographiclib libnmea libosmscout config-proto)

