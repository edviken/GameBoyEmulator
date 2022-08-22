cmake_minimum_required(VERSION 3.22)
project(GameBoyEmulator)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

# Option to enable build of testing. Default value is ON.
option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(test)
endif()