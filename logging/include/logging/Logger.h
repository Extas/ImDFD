#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

class Logger {
public:
  static auto GetLogger() -> std::shared_ptr<spdlog::logger> &;

  static void Init();
  static void Trace(const char *message);
  static void Info(const char *message);
  static void Warn(const char *message);
  static void Error(const char *message);
  static void Critical(const char *message);

private:
  inline static std::shared_ptr<spdlog::logger> s_Logger;
};

#endif // LOGGER_H