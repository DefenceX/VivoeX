## Here you can set the default 'dummy' camera feed images
set(UK_IMAGE_PATH ${CMAKE_SOURCE_DIR}/images/uk)
set(AU_IMAGE_PATH ${CMAKE_SOURCE_DIR}/images/au)

if (MSYS)
  include(${CMAKE_SOURCE_DIR}/scripts/cmake/install-msys.cmake)
else()
  include(${CMAKE_SOURCE_DIR}/scripts/cmake/install-linux.cmake)
endif()
