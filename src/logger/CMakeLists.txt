add_library(loggerLib STATIC
        ${CMAKE_SOURCE_DIR}/src/logger/Logger.cpp
        # Include headers for better IDE support
        ${CMAKE_SOURCE_DIR}/include/logger/logger/Logger.hpp
        )

target_include_directories(loggerLib PUBLIC
        ${CMAKE_SOURCE_DIR}/include/logger
        )