#include <Logger.h>

void Logger::Init() {
  // Create console sink
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

  // Create file sink
  auto file_sink =
      std::make_shared<spdlog::sinks::basic_file_sink_mt>("imdfd.log", true);

  // Create logger with both console and file sinks
  s_Logger = std::make_shared<spdlog::logger>(
      "main", spdlog::sinks_init_list{console_sink, file_sink});

  // Set log level
  s_Logger->set_level(spdlog::level::trace);

  // Set pattern
  spdlog::set_pattern("[%H:%M:%S.%e] [%^%l%$] %v");

  atexit([]() {
    Logger::GetLogger()->flush();
    spdlog::shutdown();
  });
}

void Logger::Trace(const char *message) {
  s_Logger->trace(message);
}

void Logger::Info(const char *message) {
  s_Logger->info(message);
}

void Logger::Warn(const char *message) {
  s_Logger->warn(message);
}

void Logger::Error(const char *message) {
  s_Logger->error(message);
}

void Logger::Critical(const char *message) {
  s_Logger->critical(message);
}

std::shared_ptr<spdlog::logger> &Logger::GetLogger() {
  return s_Logger;
}
