add_executable(GameBoyEmulator ${CMAKE_SOURCE_DIR}/src/app/main.cpp)

target_link_libraries(GameBoyEmulator PUBLIC
        disassemblerLib
        cpu
        memory
        )