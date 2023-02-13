## Windows
set(CPACK_GENERATOR "WIX")

set (A_PACK_DESCRIPTION_SUMMARY "${PROJECT_NAME} - CMake Assistant Solution")
set (A_INSTALL_PREFIX Consolas)

# SET(CMAKE_INSTALL_PREFIX "C:/Program Files x86/vivoe-lite" CACHE PATH "Install path" FORCE)
SET(CPACK_SET_DESTDIR FALSE)
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "vivoe-lite")
SET(CPACK_PACKAGING_INSTALL_PREFIX "")

set(CPACK_COMPONENTS_ALL applications)
set(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "Vivoe Lite")

set(CPACK_PACKAGING_INSTALL_PREFIX "vivoe-lite")
set(CPACK_WIX_PRODUCT_GUID "a19cc271-5031-4579-b0a1-d0f541354291") 
set(CPACK_WIX_PRODUCT_ICON ${CMAKE_SOURCE_DIR}/images/favicon.ico)
set(CPACK_WIX_LICENSE_RTF ${CMAKE_SOURCE_DIR}/LICENSE)
set(CPACK_WIX_ARCHITECTURE x64)

# set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
# set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ Headers")
# # Human readable component descriptions
# set(CPACK_COMPONENT_APPLICATIONS_DESCRIPTION
#   "An extremely useful application that makes use of MyLib")
# set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION
#   "Static libraries used to build programs with MyLib")
# set(CPACK_COMPONENT_HEADERS_DESCRIPTION
#   "C/C++ header files for use with MyLib")
# # Define dependencies between components
# set(CPACK_COMPONENT_HEADERS_DEPENDS libraries)
# # Define groups
# set(CPACK_COMPONENT_APPLICATIONS_GROUP "Runtime")
# set(CPACK_COMPONENT_LIBRARIES_GROUP "Development")
# set(CPACK_COMPONENT_HEADERS_GROUP "Development")
# set(CPACK_COMPONENT_GROUP_DEVELOPMENT_DESCRIPTION
#    "All of the tools you'll ever need to develop software")
# # Define NSIS installation types
# set(CPACK_ALL_INSTALL_TYPES Full Developer)
# set(CPACK_COMPONENT_LIBRARIES_INSTALL_TYPES Developer Full)
# set(CPACK_COMPONENT_HEADERS_INSTALL_TYPES Developer Full)
# set(CPACK_COMPONENT_APPLICATIONS_INSTALL_TYPES Full)

