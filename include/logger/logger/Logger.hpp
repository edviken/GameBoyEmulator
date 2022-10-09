//
// Created by Martin Edviken on 2022-09-13.
//

#ifndef GAMEBOYEMULATOR_LOGGER_HPP
#define GAMEBOYEMULATOR_LOGGER_HPP

#include <string.h>
#include <cstdint>
#include <iostream>

//namespace logger {

class Logger {
 public:
  enum class LogLevel : uint8_t { Debug, Info, Warning, Error, Panic };

  Logger() = default;

  void log(LogLevel level, std::string fileName, int lineNum, const char* fmt...) const;

 private:
  [[nodiscard]] std::string getTime() const;
};

extern Logger globalLogger;

// Note: Order of if/if-else here is important since clang also defines __GNUC__
#if defined(__clang__)  // If using clang compiler
// Nothing to do, __FILE_NAME__ already defined by clang
#elif defined(__GNUC__) || defined(__GNUG__)  // If using GCC compiler
#define __FILE_NAME__ strrchr("/" __FILE__, '/') + 1
#elif defined(_MSC_VER)  // If using MSVC compiler
#endif

#define LOG_DEBUG(...) globalLogger.log(Logger::LogLevel::Debug, __FILE_NAME__, __LINE__, __VA_ARGS__);
#define LOG_INFO(...) globalLogger.log(Logger::LogLevel::Info, __FILE_NAME__, __LINE__, __VA_ARGS__);
#define LOG_WARNING(...) globalLogger.log(Logger::LogLevel::Warning, __FILE_NAME__, __LINE__, __VA_ARGS__);
#define LOG_ERROR(...) globalLogger.log(Logger::LogLevel::Error, __FILE_NAME__, __LINE__, __VA_ARGS__);
#define LOG_PANIC(...) globalLogger.log(Logger::LogLevel::Panic, __FILE_NAME__, __LINE__, __VA_ARGS__);

//}  // namespace logger

#endif  //GAMEBOYEMULATOR_LOGGER_HPP
