
# The test program is used to ganerate all the widgets, argument 1 is 1millisecond delay in displaying images
add_custom_target(doxygen-images COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/widget-tester -t 1 -o ./images)
add_dependencies(doxygen-images widget-tester)

add_custom_target(doxygen-images-convert COMMAND convert ${CMAKE_BINARY_DIR}/images/*.png -trim +repage  -set filename:f '%t' ${CMAKE_BINARY_DIR}/images/doxygen/'%[filename:f].png')
add_dependencies(doxygen-images-convert doxygen-images)

set(ENV{'SEM_VERSION'} ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION})
set(SEM_VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION})
message(STATUS "Setup doxygen version ${SEM_VERSION} ${GIT_HASH}")
add_custom_target(doxygen COMMAND IMAGE_DIR=${CMAKE_BINARY_DIR}/images/doxygen SEM_VERSION=${SEM_VERSION} GIT_HASH=${GIT_HASH} doxygen WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

# Move any changed images over into source to be checked in
# We cannot check PNG files directly as the header changes after each generation so do a pixel by pixel check to fin differancesS
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/images/doxygen/)
file(GLOB PNG_FILES ${CMAKE_BINARY_DIR}/images/doxygen/*.png)
foreach(FILENAME_FULL ${PNG_FILES})
  get_filename_component(FILENAME_ONLY ${FILENAME_FULL} NAME)
  execute_process(COMMAND compare -metric AE ${FILENAME_FULL} ${CMAKE_SOURCE_DIR}/images/doxygen/${FILENAME_ONLY} ${CMAKE_BINARY_DIR}/diff.png ERROR_VARIABLE PIXELS_DIFF OUTPUT_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
  if (NOT PIXELS_DIFF MATCHES "0")
    message(STATUS "PNG file '${FILENAME_ONLY}' has changed with ${PIXELS_DIFF} pixels differing, copied into source")
    execute_process(COMMAND cp ${FILENAME_FULL} ${CMAKE_SOURCE_DIR}/images/doxygen/${FILENAME_ONLY})
  endif()

endforeach()

add_dependencies(doxygen doxygen-images-convert)