project(widget-tester)

include(FindPkgConfig)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(CAIRO REQUIRED cairo)

set(SOURCE_FILES widget-tester.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../hmicore/renderer_gva.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../hmicore/renderer.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../hmicore/renderer_cairo.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../hmicore/config_reader.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../hmicore/events_gva.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../hmicore/touch_gva.cc 
    ${CMAKE_CURRENT_SOURCE_DIR}/../hmicore/hmi_gva_helpers.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/../hmicore/gva_functions_common.cc
)

include_directories(
    ${CMAKE_BINARY_DIR}/external/libnmea/build/src
    ${CMAKE_BINARY_DIR}/external/libnmea/src/include
    ${CMAKE_BINARY_DIR}/external/mediax/src/src
    ${CMAKE_BINARY_DIR}/external/install/usr/local/include/
    ${OSMSCOUT_INCLUDE_DIRS}
)

link_directories(${CMAKE_BINARY_DIR}/external/libnmea/build/src)
link_directories(${CMAKE_BINARY_DIR}/external/install/usr/local/lib)
link_directories(${CMAKE_BINARY_DIR}/external/install/usr/lib64)

# OSMScout
include_directories(${CMAKE_SOURCE_DIR}/src)
link_libraries(-lstdc++fs)

add_executable(widget-tester ${SOURCE_FILES})
target_link_libraries(widget-tester pthread
    ${CAIRO_LIBRARIES} 
    ${GEOGRAPHIC_LIBRARIES} 
	${GFLAGS_LIBS} 
	${GTK3_LIBRARIES}
	${OSMSCOUT_LIBARAIES} 
	${PANGO_LIBRARIES} 
	${PORTAUDIO_LIBRARIES}
	${PROTOBUF_LIBRARY} 
	${SNDFILE_LIBRARIES}
	${SWSCALE_LIBRARIES} 
	${WINDOWS_RESOURCE_LIB} 
	GeographicLib 
	config-proto  
	nmea 
	png 
	pthread 
	stdc++fs
	mediax 
	widgets 
    hmiupdater 
	glog 
)
target_compile_options(widget-tester PUBLIC ${CAIRO_CFLAGS_OTHER} ${GTK3_CFLAGS_OTHER})
set_target_properties(widget-tester PROPERTIES UNITY_BUILD OFF)

if (MSYS)
    # Static link libraries .dll
    target_link_directories(widget-tester BEFORE PRIVATE
    "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/gflags/lib"
    "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/glog/lib"
    "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/protobuf/lib"
    "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/libosmscout/lib"
    "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/nmea/lib"
    "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/GeographicLib/lib64"
    "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/portaudio/lib"
    "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/mediax/lib"    
    "${CMAKE_BINARY_DIR}/external/install/mingw64/lib"
    )
	target_link_libraries(widget-tester shlwapi)
else()
    target_link_directories(widget-tester BEFORE PRIVATE 
		${CMAKE_BINARY_DIR}/external/libprotobuf/build
		${GLOG_LIBRARY_DIR} 
		${PROTOBUF_LIBRARY_DIR} 
		${GTEST_LIBRARY_DIRS})
endif()

add_dependencies(widget-tester libglog geographiclib libnmea libosmscout config-proto)

