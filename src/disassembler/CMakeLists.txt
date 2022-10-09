add_library(disassemblerLib STATIC
        ${CMAKE_SOURCE_DIR}/src/disassembler/Cartridge.cpp
        ${CMAKE_SOURCE_DIR}/src/disassembler/mbc/MemoryBankController.cpp
        ${CMAKE_SOURCE_DIR}/src/disassembler/Loader.cpp
        )

target_include_directories(disassemblerLib PUBLIC
        ${CMAKE_SOURCE_DIR}/include/disassembler/
        ${CMAKE_SOURCE_DIR}/include/cpu/
        )

target_link_libraries(disassemblerLib PRIVATE
        loggerLib
        )

target_compile_options(disassemblerLib PUBLIC -Wno-unused-parameter)