
# The test program is used to ganerate all the widgets, argument 1 is 1millisecond delay in displaying images
add_custom_target(doxygen-images COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/widget-tester -t 1)
add_dependencies(doxygen-images widget-tester)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/images/doxygen/)
add_custom_target(doxygen-images-convert COMMAND convert ${CMAKE_BINARY_DIR}/*.png -trim +repage  -set filename:f '%t' ${CMAKE_BINARY_DIR}/images/doxygen/'%[filename:f].png')
add_dependencies(doxygen-images-convert doxygen-images)

set(ENV{'SEM_VERSION'} ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION})
set(SEM_VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION})
message(STATUS "Setup doxygen version ${SEM_VERSION} ${GIT_HASH}")
add_custom_target(doxygen COMMAND IMAGE_PATH=${CMAKE_BINARY_DIR}/images/doxygen SEM_VERSION=${SEM_VERSION} GIT_HASH=${GIT_HASH} doxygen WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_dependencies(doxygen doxygen-images-convert)