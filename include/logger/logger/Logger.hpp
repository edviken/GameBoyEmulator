//
// Created by Martin Edviken on 2022-09-13.
//

#ifndef GAMEBOYEMULATOR_LOGGER_HPP
#define GAMEBOYEMULATOR_LOGGER_HPP

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

#define LOG_DEBUG(str, ...) globalLogger.log(Logger::LogLevel::Debug, __FILE_NAME__, __LINE__, str, ##__VA_ARGS__);
#define LOG_INFO(str, ...) globalLogger.log(Logger::LogLevel::Info, __FILE_NAME__, __LINE__, str, ##__VA_ARGS__);
#define LOG_WARNING(str, ...) globalLogger.log(Logger::LogLevel::Warning, __FILE_NAME__, __LINE__, str, ##__VA_ARGS__);
#define LOG_ERROR(str, ...) globalLogger.log(Logger::LogLevel::Error, __FILE_NAME__, __LINE__, str, ##__VA_ARGS__);
#define LOG_PANIC(str, ...) globalLogger.log(Logger::LogLevel::Panic, __FILE_NAME__, __LINE__, str, ##__VA_ARGS__);

//}  // namespace logger

#endif  //GAMEBOYEMULATOR_LOGGER_HPP
