include(FindPkgConfig)
project(hmi-display)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
# pkg_check_modules(CAIRO REQUIRED cairo)
# pkg_check_modules(PANGO REQUIRED pango)
pkg_check_modules(SWSCALE REQUIRED libswscale)

add_subdirectory(src/widgets)
add_subdirectory(common)
add_subdirectory(config)
add_subdirectory(tools)
#add_subdirectory(dds)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/hmi-display)
include_directories(${CMAKE_BINARY_DIR}/external/vivoe-media-framework/src)
include_directories(${CMAKE_BINARY_DIR}/external/libnmea/src/include)

link_directories(${CMAKE_BINARY_DIR}/external/vivoe-media-framework/build)
link_directories(${CMAKE_BINARY_DIR}/external/libnmea/build/src)

set(SOURCES main.cc 
			# src/trace.cc
			src/gva_application.cc
			src/gva_functions_common.cc
			src/renderer.cc 
			src/renderer_cairo.cc 
			src/renderer_gva.cc 
			src/touch_gva.cc 
			src/screen_gva.cc 
			src/events_gva.cc 
			src/widgets/widget.cc
			src/widgets/keyboard.cc
			src/widgets/driver/rpm_fuel.cc
			src/widgets/driver/speedometer.cc
			src/widgets/table/table.cc
			src/widgets/table/table_dynamic.cc
			src/widgets/table/cell_type.cc
			src/widgets/table/row_type.cc
			src/widgets/plan_position_indicator.cc
			src/widgets/top_labels.cc
			src/widgets/bottom_labels.cc
			src/widgets/side_labels.cc
			src/widgets/mode.cc
			src/widgets/alarm_indicator.cc
			common/debug.cc 
			common/utils.cc 
			src/hmi_gva.cc 
			src/hmi_gva_defaults.cc 
			src/hmi_gva_helpers.cc 
			src/view_gva.cc 
			src/renderer_map.cc 
			src/config_reader.cc
			src/states/on.cc
			src/states/off.cc
			src/states/sa.cc
			src/states/wpn.cc
			src/states/sys.cc
			src/states/def.cc
			src/states/drv.cc
			src/states/com.cc
			src/states/str.cc
			src/states/bms.cc
			src/states/alarms.cc
			)

link_libraries(-lstdc++fs)
add_executable(hmi-display ${SOURCES})
add_dependencies(hmi-display libglog libprotobuf googletest libosmscout geographiclib hmi-video config-proto ${DDS_STACK} libosmscout)

link_directories( ${NMEA_LIBRARY_DIR} ${CMAKE_BINARY_DIR}/external/libnmea/src/lib )
target_link_libraries (hmi-display ${GEOGRAPHIC_LIBRARIES} ${WINDOWS_RESOURCE_LIB} glog GeographicLib config-proto ${OSMSCOUT_LIBARAIES} ${PROTOBUF_LIBRARY} ${GTK_LIBRARIES3} stdc++fs)
target_link_libraries(hmi-display png pthread hmi-video vivoe-media nmea config-proto ${PROTOBUF_LIBRARY} ${GFLAGS_LIBS} ${CAIRO_LIBRARIES} ${PANGO_LIBRARIES} ${SWSCALE_LIBRARIES} ${GTK3_LIBRARIES})

if (MSYS)
	# Add the resource file
	target_link_libraries(hmi-display ${WINDOWS_RESOURCE})
	# Static link libraries .a
	target_link_directories(hmi-display BEFORE PRIVATE
		"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/protobuf/lib"
		"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/gflags/lib"
		"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/glog/lib"
		"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/protobuf/lib"
		"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/libosmscout/lib"
		"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/nmea/lib"
		"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/GeographicLib/lib64"
	)
	target_link_libraries(hmi-display shlwapi)
else()
	target_link_directories(hmi-display PRIVATE
		${CMAKE_BINARY_DIR}/external/libprotobuf/build
		${GEOGRAPHIC_LIBRARY_DIRS}
		${GLOG_LIBRARY_DIR}
		${GTEST_LIBRARY_DIRS}
		${NMEA_LIBRARY_DIR}
		${CMAKE_BINARY_DIR}/external/libnmea/src/lib/
		${CMAKE_BINARY_DIR}/external/install/usr/local/lib
	)
endif()

target_include_directories(hmi-display PUBLIC 
    ${NMEA_INCLUDER_DIRS} 
    ${OSMSCOUT_INCLUDE_DIRS} 
    ${GEOGRAPHIC_INCLUDE_DIRS}
    ${CMAKE_BINARY_DIR}/hmi-display/config
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${CMAKE_BINARY_DIR}/hmi_display
    ${CAIRO_INCLUDE_DIRS}
    ${PANGO_INCLUDE_DIRS}
    ${SWSCALE_INCLUDE_DIRS}
    ${GTK3_INCLUDE_DIRS}
    common 
    dds 
    dds/location 
    display)
target_compile_options(hmi-display PUBLIC ${CAIRO_CFLAGS_OTHER} ${GTK3_CFLAGS_OTHER})
set_target_properties(hmi-display PROPERTIES UNITY_BUILD OFF)


