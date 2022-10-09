add_library(memory STATIC
        ${CMAKE_SOURCE_DIR}/src/memory/Memory.cpp
        # Include headers for better IDE support
        ${CMAKE_SOURCE_DIR}/include/memory/memory/Memory.hpp
        )

target_include_directories(memory PUBLIC
        ${CMAKE_SOURCE_DIR}/include/memory
        )