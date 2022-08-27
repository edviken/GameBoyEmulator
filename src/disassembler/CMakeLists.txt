add_library(disassemblerLib STATIC
        ${CMAKE_SOURCE_DIR}/src/disassembler/Cartridge.cpp
        ${CMAKE_SOURCE_DIR}/src/disassembler/MemoryBankController.cpp
        )

target_include_directories(disassemblerLib PUBLIC
        ${CMAKE_SOURCE_DIR}/include/disassembler/
        )