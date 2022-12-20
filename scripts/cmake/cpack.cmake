project (vivoe-lite-packages)

# Create systems integration files
file(WRITE ${CMAKE_BINARY_DIR}/etc/ld.so.conf.d/vivoe-lite.conf "/opt/gva/libs/\n") 
file(WRITE ${CMAKE_BINARY_DIR}/etc/profile.d/vivoe-lite.sh "export PATH=$PATH:/opt/gva/hmi\n")

#General
set(VERSION "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}")
set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_GENERATOR "RPM")
if ("${DDS}" STREQUAL "CYCLONE-CE")
  set(CPACK_PACKAGE_NAME "vivoe-lite-cyclone-ce")
elseif ("${DDS}" STREQUAL "OSPL-CE")
  set(CPACK_PACKAGE_NAME "vivoe-lite-ospl-ce")
elseif("${DDS}" STREQUAL "RTI")
  set(CPACK_PACKAGE_NAME "vivoe-lite-connext")
elseif()
  message(ERROR "DDS vendor not currently supported (${DDS})")
endif()
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_CONTACT "Ross Newman")
set(CPACK_PACKAGE_VENDOR "DefenceX")
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")
set(CPACK_RPM_PACKAGE_RELEASE epl8)
set(CPACK_RPM_PACKAGE_RELEASE_DIST YES)
set(CPACK_RPM_PACKAGE_NAME  "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.epl8.${CMAKE_SYSTEM_PROCESSOR}")
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST "/opt")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST "/etc/profile.d")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST "/usr/local")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST "/var")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST "/var/log")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST "/etc")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST "/etc/ld.so.conf.d")

# Debian
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Ross Newman")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libcairo2, libxt6, libxext6, libswscale5, libprotobuf23")
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "ldconfig")
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake/postinst")

# package name for deb. If set, then instead of some-application-0.9.2-Linux.deb
# you'll get some-application_0.9.2_amd64.deb (note the underscores too)
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
# that is if you want every group to have its own package,
# although the same will happen if this is not set (so it defaults to ONE_PER_GROUP)
# and CPACK_DEB_COMPONENT_INSTALL is set to YES
set(CPACK_COMPONENTS_GROUPING ALL_COMPONENTS_IN_ONE)#ONE_PER_GROUP)
# without this you won't be able to pack only specified component
set(CPACK_DEB_COMPONENT_INSTALL YES)
include(CPack)

# CPack 
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake/vivoe-lite.spec.in" "${CMAKE_CURRENT_BINARY_DIR}/vivoe-lite.spec" @ONLY IMMEDIATE)
set(CPACK_RPM_USER_BINARY_SPECFILE "${CMAKE_CURRENT_BINARY_DIR}/vivoe-lite.spec")

