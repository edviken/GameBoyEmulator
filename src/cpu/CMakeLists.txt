add_library(cpu STATIC
        ${CMAKE_SOURCE_DIR}/src/cpu/Cpu.cpp
        ${CMAKE_SOURCE_DIR}/src/cpu/decoder/Decoder.cpp
        ${CMAKE_SOURCE_DIR}/src/cpu/register/Register.cpp
        )

target_include_directories(cpu PUBLIC
        ${CMAKE_SOURCE_DIR}/include/cpu
        )

