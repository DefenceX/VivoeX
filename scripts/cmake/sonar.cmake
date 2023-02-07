add_custom_target(sonar)    
add_custom_command(
    TARGET sonar
    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/bw-output
    COMMAND build-wrapper-linux-x86-64 --out-dir ./build/bw-output cmake --build ./build --clean-first --target all -- -j4
    COMMAND SONAR_TOKEN=2846eb125a3eb562f02271c1409fbf57fba9106f PATH=/tools/sonar-scanner-4.7.0.2747-linux/bin:/tools/build-wrapper-linux-x86:$PATH 
    COMMAND sonar-scanner
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
