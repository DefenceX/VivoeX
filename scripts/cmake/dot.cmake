



add_custom_target(dot
    COMMAND ${CMAKE_COMMAND} "--graphviz=cmake.dot" .
    COMMAND dot -Tpng cmake.dot -o images/doxygen/cmake.png
    COMMAND convert -resize 800 images/doxygen/cmake.png  images/doxygen/cmake.png
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)


