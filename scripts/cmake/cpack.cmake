project (vivoe-lite)

# Create systems integration files
file(WRITE ${CMAKE_BINARY_DIR}/etc/ld.so.conf.d/vivoe-lite.conf "/opt/gva/libs/\n") 
file(WRITE ${CMAKE_BINARY_DIR}/etc/profile.d/vivoe-lite.sh "export PATH=$PATH:/opt/gva/hmi\n")

#General
set(VERSION "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}")
set(CPACK_PACKAGE_NAME vivoe-lite)
set(CPACK_PACKAGE_VERSION_MAJOR ${CMAKE_MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${CMAKE_MINOR_VERSION})
set(CPACK_PACKAGE_VERSION_PATCH ${CMAKE_PATCH_VERSION})
set(CPACK_PACKAGE_VERSION ${VERSION})
if ("${DDS}" STREQUAL "CYCLONE-CE")
  set(CPACK_PACKAGE_NAME "vivoe-lite-cyclone-ce")
elseif ("${DDS}" STREQUAL "OSPL-CE")
  set(CPACK_PACKAGE_NAME "vivoe-lite-ospl-ce")
elseif("${DDS}" STREQUAL "RTI")
  set(CPACK_PACKAGE_NAME "vivoe-lite-connext")
elseif()
  message(ERROR "DDS vendor not currently supported (${DDS})")
endif()

set(CPACK_PACKAGE_CONTACT "Ross Newman")
set(CPACK_PACKAGE_VENDOR "DefenceX")

if (MSYS)
  include(${CMAKE_SOURCE_DIR}/scripts/cmake/cpack-msys.cmake)
else()
  include(${CMAKE_SOURCE_DIR}/scripts/cmake/cpack-deb.cmake)
  include(${CMAKE_SOURCE_DIR}/scripts/cmake/cpack-rpm.cmake)
endif()

set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_SYSTEM_NAME}")

include(CPack)

