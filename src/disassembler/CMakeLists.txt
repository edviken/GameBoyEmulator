add_library(disassemblerLib STATIC
        ${CMAKE_SOURCE_DIR}/src/disassembler/CartridgeLoader.cpp
        ${CMAKE_SOURCE_DIR}/src/disassembler/mbc/MemoryBankController.cpp
        )

target_include_directories(disassemblerLib PUBLIC
        ${CMAKE_SOURCE_DIR}/include/disassembler/
        ${CMAKE_SOURCE_DIR}/include/cpu/
        )

target_link_libraries(disassemblerLib PRIVATE
        loggerLib
        )