install(TARGETS hmi-display)
file(GLOB_RECURSE OSMSCOUT_DLL "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/libosmscout/bin/*.dll")
install(FILES ${OSMSCOUT_DLL} DESTINATION bin)
install(FILES "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/GeographicLib/bin/libGeographicLib.dll" DESTINATION bin)
install(FILES "${CMAKE_BINARY_DIR}/external/install/usr/local/lib/libvivoe-media.dll" DESTINATION bin)
install(FILES "${CMAKE_BINARY_DIR}/external/install/Program Files (x86)/glog/bin/libglog.dll" DESTINATION bin)
# install(FILES "${CMAKE_SOURCE_DIR}/scripts/Vivoe Lite.lnk" DESTINATION $ENV{USERPROFILE}/Desktop)
## MSYS libs now
install(FILES 
    C:/msys64/mingw64/bin/libcairo-2.dll
    C:/msys64/mingw64/bin/libgcc_s_seh-1.dll
    C:/msys64/mingw64/bin/libgtk-3-0.dll
    C:/msys64/mingw64/bin/libglib-2.0-0.dll
    C:/msys64/mingw64/bin/libgio-2.0-0.dll
    C:/msys64/mingw64/bin/libgobject-2.0-0.dll
    C:/msys64/mingw64/bin/libgdk-3-0.dll
    C:/msys64/mingw64/bin/libstdc++-6.dll
    C:/msys64/mingw64/bin/libwinpthread-1.dll
    C:/msys64/mingw64/bin/libpango-1.0-0.dll
    C:/msys64/mingw64/bin/libpangocairo-1.0-0.dll
    C:/msys64/mingw64/bin/libiconv-2.dll
    C:/msys64/mingw64/bin/libpng16-16.dll
    C:/msys64/mingw64/bin/libintl-8.dll
    C:/msys64/mingw64/bin/swscale-5.dll
    C:/msys64/mingw64/bin/libprotobuf.dll
    C:/msys64/mingw64/bin/zlib1.dll
    C:/msys64/mingw64/bin/libfreetype-6.dll
    C:/msys64/mingw64/bin/libfontconfig-1.dll
    C:/msys64/mingw64/bin/libpixman-1-0.dll
    C:/msys64/mingw64/bin/libepoxy-0.dll
    C:/msys64/mingw64/bin/libcairo-gobject-2.dll
    C:/msys64/mingw64/bin/libgdk_pixbuf-2.0-0.dll
    C:/msys64/mingw64/bin/libfribidi-0.dll
    C:/msys64/mingw64/bin/libgmodule-2.0-0.dll
    C:/msys64/mingw64/bin/libpcre2-8-0.dll
    C:/msys64/mingw64/bin/libffi-8.dll
    C:/msys64/mingw64/bin/libpangowin32-1.0-0.dll
    C:/msys64/mingw64/bin/libatk-1.0-0.dll
    C:/msys64/mingw64/bin/libharfbuzz-0.dll
    C:/msys64/mingw64/bin/libthai-0.dll
    C:/msys64/mingw64/bin/avutil-56.dll
    C:/msys64/mingw64/bin/libpangoft2-1.0-0.dll
    C:/msys64/mingw64/bin/libgflags.dll
    C:/msys64/mingw64/bin/libbrotlidec.dll
    C:/msys64/mingw64/bin/libbz2-1.dll
    C:/msys64/mingw64/bin/libexpat-1.dll
    C:/msys64/mingw64/bin/libmfx-1.dll
    C:/msys64/mingw64/bin/libgraphite2.dll
    C:/msys64/mingw64/bin/libdatrie-1.dll
    C:/msys64/mingw64/bin/libbrotlicommon.dll
    DESTINATION bin
    COMPONENT application)
# Images for dummy camera feeds
install(FILES  
    ${AU_IMAGE_PATH}/FrontRight.png 
    ${AU_IMAGE_PATH}/FrontCenter.png 
    ${AU_IMAGE_PATH}/FrontLeft.png 
    ${AU_IMAGE_PATH}/Right.png 
    ${AU_IMAGE_PATH}/Rear.png 
    ${AU_IMAGE_PATH}/Left.png 
    ${AU_IMAGE_PATH}/Quad.png 
    DESTINATION images
    COMPONENT aus_imagry)
# All other images
install(FILES  
    ${CMAKE_SOURCE_DIR}/images/screen/DefenceX.png 
    DESTINATION images)

