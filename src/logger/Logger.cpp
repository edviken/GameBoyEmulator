//
// Created by Martin Edviken on 2022-09-13.
//

#include "logger/Logger.hpp"
#include <cstdarg>
#include <ctime>

//namespace logger {

Logger globalLogger;

void Logger::log(const Logger::LogLevel level, std::string fileName, int lineNum, const char* fmt...) const {
  std::string logLevel{};
  switch (level) {
    case LogLevel::Debug:
      logLevel = "DEBUG";
      break;
    case LogLevel::Info:
      logLevel = "INFO";
      break;
    case LogLevel::Warning:
      logLevel = "WARNING";
      break;
    case LogLevel::Error:
      logLevel = "ERROR";
      break;
    case LogLevel::Panic:
      logLevel = "PANIC";
      break;
  }

  // Capture the message from the LOG_X variadic args and print
  size_t outputBufferSize = 250;
  char str[outputBufferSize];
  va_list args;
  va_start(args, fmt);
  vsnprintf(str, outputBufferSize, fmt, args);
  va_end(args);

  // clang-format off
  std::cout <<  "["
            << getTime()
            << "] "
            << logLevel
            << " "
            << fileName
            << ":"
            << lineNum
            << "\t"
            << str
            << std::endl;
  // clang-format on
}

std::string Logger::getTime() const {
  std::time_t result = std::time(nullptr);
  std::string str(std::asctime(std::localtime(&result)));
  str.erase(std::remove(str.begin(), str.end(), '\n'), str.cend());
  return str;
}

//}  // namespace logger