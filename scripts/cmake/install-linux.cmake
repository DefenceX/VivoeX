install(TARGETS hmi-display DESTINATION /opt/gva/hmi)

# Create systems integration files
file(WRITE ${CMAKE_BINARY_DIR}/etc/ld.so.conf.d/vivoe-lite.conf "/opt/gva/libs/\n") 
file(WRITE ${CMAKE_BINARY_DIR}/etc/profile.d/vivoe-lite.sh "export PATH=$PATH:/opt/gva/hmi\n")
install(DIRECTORY DESTINATION /etc/ld.so.conf.d)
install(DIRECTORY DESTINATION /etc/profile.d)
# Install binaries with external libs
install(FILES ${CMAKE_BINARY_DIR}/external/vivoe-media-framework/build/libvivoe-media.so DESTINATION "/opt/gva/libs" PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE)
install(FILES ${CMAKE_BINARY_DIR}/etc/ld.so.conf.d/vivoe-lite.conf DESTINATION "/etc/ld.so.conf.d" PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ) 
install(FILES ${CMAKE_BINARY_DIR}/etc/profile.d/vivoe-lite.sh DESTINATION "/etc/profile.d" PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)
# Glob files, can be in different locations for different distros
file(GLOB_RECURSE DDS_LIBS ${CMAKE_BINARY_DIR}/external/install/usr/*libcyclone*.so*)
file(GLOB_RECURSE GLOG_LIBS ${CMAKE_BINARY_DIR}/external/install/usr/*libglog*.so*)
install(FILES  
            ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libvivoe-media.so
            ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libvivoe-media.so.1
            ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libGeographicLib.so
            ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libGeographicLib.so.23
            ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libGeographicLib.so.23.1.0
            ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libosmscout_import.so 
            ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libosmscout_import.so.1.1.1
            ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libosmscout_map_cairo.so
            ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libosmscout_map_cairo.so.1.1.1
            ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libosmscout_map.so
            ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libosmscout_map.so.1.1.1
            ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libosmscout.so
            ${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libosmscout.so.1.1.1
            # ${CMAKE_BINARY_DIR}/external/install/opt/cairo/lib/lib/
            # ${CMAKE_BINARY_DIR}/external/install/lib/${ARCH}-linux-gnu/libpango-1.0.so
            # ${CMAKE_BINARY_DIR}/external/install/lib/${ARCH}-linux-gnu/libpangocairo-1.0.so
            ${GLOG_LIBS}
            ${DDS_LIBS}
        DESTINATION "/opt/gva/libs" PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_WRITE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_WRITE WORLD_EXECUTE)

# Images for dummy camera feeds
install(FILES  
    ${IMAGE_PATH}/FrontRight.png 
    ${IMAGE_PATH}/FrontCenter.png 
    ${IMAGE_PATH}/FrontLeft.png 
    ${IMAGE_PATH}/Right.png 
    ${IMAGE_PATH}/Rear.png 
    ${IMAGE_PATH}/Left.png 
    ${IMAGE_PATH}/Quad.png 
    DESTINATION "/opt/gva/hmi/images")

# All other images
install(FILES  
    ${CMAKE_SOURCE_DIR}/images/screen/DefenceX.png 
    DESTINATION "/opt/gva/hmi/images")

