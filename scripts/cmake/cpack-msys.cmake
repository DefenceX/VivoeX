set(CPACK_GENERATOR "NSIS")

## Windows
# set(A_PACK_DESCRIPTION_SUMMARY "${PROJECT_NAME} - A GVA compliant HMI for military applications")
# set(A_INSTALL_PREFIX Consolas)
set(CPACK_SYSTEM_NAME win64)
# set(CPACK_SET_DESTDIR FALSE)
set(CPACK_PACKAGE_INSTALL_DIRECTORY "vivoe-lite")
set(CPACK_COMPONENTS_ALL COMPONENTS)
set(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "Vivoe Lite")
set(CPACK_PACKAGING_INSTALL_PREFIX "vivoe-lite")

# NSIS
set(CPACK_NSIS_MUI_ICON ${CMAKE_SOURCE_DIR}/images/favicon.ico)
set(CPACK_NSIS_MUI_UNIICON ${CMAKE_SOURCE_DIR}/images/favicon.ico)
set(CPACK_NSIS_MUI_WELCOMEFINISHPAGE_BITMAP ${CMAKE_SOURCE_DIR}\\\\images\\\\NSIS_Installer.bmp)
set(CPACK_NSIS_MUI_UNWELCOMEFINISHPAGE_BITMAP ${CMAKE_SOURCE_DIR}\\\\images\\\\NSIS_Installer.bmp)
set(CPACK_NSIS_COMPONENT_INSTALL OFF)
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
set(CPACK_NSIS_MODIFY_PATH OFF)
set(CPACK_NSIS_DISPLAY_NAME "Vivoe Lite installer")
set(CPACK_NSIS_PACKAGE_NAME "Vivoe Lite installer")
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)
set(CPACK_NSIS_INSTALLED_ICON_NAME ${CMAKE_SOURCE_DIR}/images/favicon.ico)
set(CPACK_NSIS_HELP_LINK "https://defencex.com.au/downloads.html")
set(CPACK_NSIS_URL_INFO_ABOUT "https://defencex.com.au")
set(CPACK_NSIS_CONTACT "enquiries@defencex.com.au")
# set(CPACK_NSIS_MENU_LINKS
#     "doc/cmake-@CMake_VERSION_MAJOR@.@CMake_VERSION_MINOR@/cmake.html"
#     "CMake Help" "https://cmake.org" "CMake Web Site")
set(CPACK_NSIS_WELCOME_TITLE "Vivoe Lite (DefenceX)")
# set(CPACK_NSIS_WELCOME_TITLE_3LINES  "three\nwelcome\nlines")
set(CPACK_NSIS_FINISH_TITLE "Installation complete...")
# set(CPACK_NSIS_FINISH_TITLE_3LINES "three\nfinish\nlines")
# set(CPACK_NSIS_MUI_HEADERIMAGE "")
# set(CPACK_NSIS_BRANDING_TEXT "This is some branding text")

# WIX
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

