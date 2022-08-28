cmake_minimum_required(VERSION 3.22)
project(GameBoyEmulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create a generated file with cmake variables that's publicly available in this project
set(PROJECT_ROOT_STRING ${CMAKE_SOURCE_DIR})
configure_file(${CMAKE_SOURCE_DIR}/external/config/root_path.h.in ${CMAKE_BINARY_DIR}/generated/generated/root_path.h @ONLY)
# Todo: Consider only having the include_dir in only modules that needs it.
include_directories( ${CMAKE_BINARY_DIR}/generated/ ) # Make sure it can be included...

add_subdirectory(src)

# Option to enable build of testing. Default value is ON.
option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(test)
endif()