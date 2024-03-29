if (MSYS)
  file(WRITE ${CMAKE_BINARY_DIR}/vivoe-lite.rc "id ICON  \"${CMAKE_SOURCE_DIR}/images/favicon.ico\"\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "  1 VERSIONINFO\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "  FILEVERSION     1,0,0,0\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "  PRODUCTVERSION  1,0,0,0\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "  BEGIN\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "    BLOCK \"StringFileInfo\"\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "    BEGIN\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "      BLOCK \"080904E4\"\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "      BEGIN\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "        VALUE \"CompanyName\", \"DefenceX\"\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "        VALUE \"FileDescription\", \"Vehicle human machine interface conforming to the Generic Vehicle Architecture (GVA)\"\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "        VALUE \"FileVersion\", \"1.0\"\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "        VALUE \"InternalName\", \"vivoe_lite\"\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "        VALUE \"LegalCopyright\", \"DefenceX\"\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "        VALUE \"OriginalFilename\", \"vivoe_lite.exe\"\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "        VALUE \"ProductName\", \"Vivoe Lite\"\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "        VALUE \"ProductVersion\", \"1.0\"\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "      END\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "    END\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "    BLOCK \"VarFileInfo\"\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "    BEGIN\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "      VALUE \"Translation\", 0x809, 1252\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "    END\n")
  file(APPEND ${CMAKE_BINARY_DIR}/vivoe-lite.rc "  END\n")

  execute_process(
    COMMAND rm ${CMAKE_BINARY_DIR}/vivoe-lite.res --force)
  execute_process(
    COMMAND windres ${CMAKE_BINARY_DIR}/vivoe-lite.rc -O coff -o ${CMAKE_BINARY_DIR}/vivoe-lite.res)

  set(WINDOWS_RESOURCE ${CMAKE_BINARY_DIR}/vivoe-lite.res)
  add_library(resources OBJECT IMPORTED ${WINDOWS_RESOURCE})
  set(WINDOWS_RESOURCE_LIB resources)


endif()

