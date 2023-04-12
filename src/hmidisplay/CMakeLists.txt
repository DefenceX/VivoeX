include(FindPkgConfig)
project(hmi-display)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(PANGO REQUIRED pango)
pkg_check_modules(SWSCALE REQUIRED libswscale)

include_directories(${CMAKE_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${OSMSCOUT_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/src
  ${CMAKE_BINARY_DIR}/external/libnmea/src/include
  ${GLOG_INCLUDE_DIRS}
  ${CAIRO_INCLUDE_DIRS}
  ${GTK3_INCLUDE_DIRS}
  ${CMAKE_BINARY_DIR}/src/config
)

link_directories(${CMAKE_BINARY_DIR}/external/vivoe-media-framework/build)
link_directories(${CMAKE_BINARY_DIR}/external/libnmea/build/src)

add_executable(hmi-display main.cc gva_application.cc)

link_directories( ${NMEA_LIBRARY_DIR} ${CMAKE_BINARY_DIR}/external/libnmea/src/lib)
target_link_libraries(hmi-display 
    hmicore
	widgets 
	pthread 
	hmiupdater
	hmiaudio
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
	glog 
	hmivideo 
	nmea 
	png 
	pthread 
	stdc++fs
	vivoe-media 
)

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
		"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/GeographicLib/lib64"
		"${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/portaudio/lib"
		"${CMAKE_BINARY_DIR}/external/install/mingw64/lib"
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
		${SNDFILE_LIBRARY_DIR}
		${PORTAUDIO_LIBRARY_DIR}
	)
endif()
	
target_compile_options(hmi-display PUBLIC ${CAIRO_CFLAGS_OTHER} ${GTK3_CFLAGS_OTHER})
set_target_properties(hmi-display PROPERTIES UNITY_BUILD OFF)


