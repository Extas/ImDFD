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

  template <typename... Args>
  static void Trace(const char *format, Args... args) {
    s_logger_->trace(format, args...);
  }

  template <typename... Args>
  static void Info(const char *format, Args... args) {
    s_logger_->info(format, args...);
  }

  template <typename... Args>
  static void Warn(const char *format, Args... args) {
    s_logger_->warn(format, args...);
  }

  template <typename... Args>
  static void Error(const char *format, Args... args) {
    s_logger_->error(format, args...);
  }

  template <typename... Args>
  static void Critical(const char *format, Args... args) {
    s_logger_->critical(format, args...);
  }

private:
  inline static std::shared_ptr<spdlog::logger> s_logger_;
};

#endif // LOGGER_H
