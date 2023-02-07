
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_C_COMPILER ${TARGET_CROSS}cc)
set(CMAKE_CXX_COMPILER ${TARGET_CROSS}c++)

set(CMAKE_FIND_ROOT_PATH ${TOOL_PATH} ${CMAKE_BINARY_DIR}/install)
set(CMAKE_FIND_ROOT_PATH_PROGRAM_MODE NEVER)

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
