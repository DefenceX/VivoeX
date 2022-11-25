project(test-hmi)

include(FindPkgConfig)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(CAIRO REQUIRED cairo)
find_package(Protobuf REQUIRED)

set(SOURCE_FILES test.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/renderer_gva.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/renderer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/renderer_cairo.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/config_reader.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/events_gva.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/widgets/widget.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/widgets/compass.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/widgets/keyboard.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/widgets/alarm_indicator.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../common/log_gva.cc
    ${PROTO_SRCS}
)

include_directories(${CMAKE_BINARY_DIR}/external/libnmea/src/include)
link_directories(${CMAKE_BINARY_DIR}/external/libnmea/build/src)

add_executable(test-hmi ${SOURCE_FILES})

target_link_libraries(test-hmi nmealib config-proto ${CAIRO_LIBRARIES} ${GTK3_LIBRARIES} )
target_include_directories(test-hmi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR}/hmi-display/config ${CMAKE_CURRENT_SOURCE_DIR}/../hmi-display${CAIRO_INCLUDE_DIRS} ${PANGO_INCLUDE_DIRS} ${GTK3_INCLUDE_DIRS})
target_compile_options(test-hmi PUBLIC ${CAIRO_CFLAGS_OTHER} ${GTK3_CFLAGS_OTHER})
add_dependencies(test-hmi libnmea config-proto)

