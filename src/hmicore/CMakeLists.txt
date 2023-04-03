add_subdirectory(widgets)

set(SOURCES ../common/debug.cc 
    ../common/utils.cc 
    config_reader.cc
    events_gva.cc 
    gva_application.cc
    gva_functions_common.cc
    hardware/audio.cc 
    hmi_gva.cc 
    hmi_gva_defaults.cc 
    hmi_gva_helpers.cc 
    renderer.cc 
    renderer_cairo.cc 
    renderer_gva.cc 
    renderer_map.cc 
    status_updater.cc 
    screen_gva.cc 
    states/alarms.cc
    states/bms.cc
    states/com.cc
    states/def.cc
    states/drv.cc
    states/off.cc
    states/on.cc
    states/sa.cc
    states/str.cc
    states/sys.cc
    states/wpn.cc
    touch_gva.cc 
    view_gva.cc 
)

add_library(hmicore STATIC ${SOURCES})
add_dependencies(hmicore widgets hmi-updater portaudio libglog libprotobuf googletest libosmscout geographiclib hmi-video config-proto ${DDS_STACK} libosmscout)
message(STATUS >>>>>>> ${NMEA_INCLUDER_DIRS} )

target_include_directories (hmicore PUBLIC
    ${NMEA_INCLUDER_DIRS} 
    ${OSMSCOUT_INCLUDE_DIRS} 
    ${GEOGRAPHIC_INCLUDE_DIRS}
    ${CMAKE_BINARY_DIR}/hmi-display/config
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${CAIRO_INCLUDE_DIRS}
    ${PANGO_INCLUDE_DIRS}
    ${SWSCALE_INCLUDE_DIRS}
    ${GTK3_INCLUDE_DIRS}  
    ${PORTAUDIO_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/src
)

