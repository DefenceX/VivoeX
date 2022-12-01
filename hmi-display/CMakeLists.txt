include(FindPkgConfig)
project(hmi-display)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(PANGO REQUIRED pango)
pkg_check_modules(SWSCALE REQUIRED libswscale)

add_subdirectory(src/widgets)
add_subdirectory(common)
add_subdirectory(config)
add_subdirectory(tools)
#add_subdirectory(dds)

if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_BINARY_DIR}/external/vivoe-media-framework/src)
include_directories(${CMAKE_BINARY_DIR}/external/libnmea/src/include)
if (ENABLE_OSMSCOUT)
	include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/src/libosmscout/include)
	include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/src/libosmscout-map/include)
	include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/src/libosmscout-map-cairo/include)
	include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/build/libosmscout/include)
	include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/build/libosmscout-map/include)
	include_directories(${CMAKE_BINARY_DIR}/external/libosmscout/build/libosmscout-map-cairo/include)
	include_directories(${PROJECT_SOURCE_DIR}/../libosmscout/libosmscout/include)
	include_directories(${PROJECT_SOURCE_DIR}/../libosmscout/libosmscout-map/include)
	include_directories(${PROJECT_SOURCE_DIR}/../libosmscout/libosmscout-map-cairo/include)
	link_directories(${CMAKE_BINARY_DIR}/external/libosmscout/build/libosmscout-map-cairo)
	link_directories(${CMAKE_BINARY_DIR}/external/libosmscout/build/libosmscout)
	link_directories(${CMAKE_BINARY_DIR}/external/libosmscout/build/libosmscout-map)
endif()
link_directories(${CMAKE_BINARY_DIR}/external/Fast-DDS/build/thirdparty/fastcdr/src/cpp)
link_directories(${CMAKE_BINARY_DIR}/external/Fast-DDS/build/src/cpp)
link_directories(${CMAKE_BINARY_DIR}/external/vivoe-media-framework/build)
link_directories(${CMAKE_BINARY_DIR}/external/libnmea/build/src)

message ("Platform " ${CMAKE_SYSTEM_NAME} " : " ${CMAKE_SYSTEM} ${MSYS} ${MSYS2}) 

set(SOURCES main.cc 
			src/gva_application.cc
			src/gva_functions_common.cc
			src/renderer.cc 
			src/renderer_cairo.cc 
			src/renderer_gva.cc 
			src/screen_gva.cc 
			src/events_gva.cc 
			src/widgets/widget.cc
			src/widgets/keyboard.cc
			src/widgets/table.cc
			src/widgets/compass.cc
			src/widgets/top_labels.cc
			src/widgets/bottom_labels.cc
			src/widgets/side_labels.cc
			src/widgets/mode.cc
			src/widgets/alarm_indicator.cc
			common/debug.cc 
			common/log_gva.cc 
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
add_executable(hmi-display ${PROTO_SRCS} ${SOURCES})
if (ENABLE_OSMSCOUT)
	add_dependencies(hmi-display config-proto hmi-video libosmscout)
        set(OSMSCOUT_LIBS osmscout osmscout_map osmscout_map_cairo)
else()
	add_dependencies(hmi-display hmi-video config-proto ${DDS_STACK})
endif()
target_link_libraries (hmi-display Geographic config-proto ${OSMSCOUT_LIBS} ${Protobuf_LIBRARIES} ${GTK_LIBRARIES3} stdc++fs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -std=c++11")

link_directories(${CMAKE_BINARY_DIR}/external/vivoe-media-framework/build ${CMAKE_BINARY_DIR}/external/libnmea/build/src)
target_link_libraries(hmi-display png pthread hmi-video vivoe-media nmealib config-proto ${CAIRO_LIBRARIES} ${PANGO_LIBRARIES} ${SWSCALE_LIBRARIES} ${GTK3_LIBRARIES})
target_include_directories(hmi-display PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR}/hmi-display/config ${CMAKE_CURRENT_SOURCE_DIR}/widgets ${CMAKE_CURRENT_SOURCE_DIR}/common ${CMAKE_BINARY_DIR}/hmi_display ${CAIRO_INCLUDE_DIRS} ${PANGO_INCLUDE_DIRS} ${SWSCALE_INCLUDE_DIRS} ${GTK3_INCLUDE_DIRS} common dds dds/location display)
target_compile_options(hmi-display PUBLIC ${CAIRO_CFLAGS_OTHER} ${GTK3_CFLAGS_OTHER})
set_target_properties(hmi-display PROPERTIES UNITY_BUILD ON)

install(TARGETS hmi-display DESTINATION /opt/gva/hmi)

