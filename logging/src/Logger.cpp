#include <logging/Logger.h>

void Logger::Init() {
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  auto file_sink =
      std::make_shared<spdlog::sinks::basic_file_sink_mt>("imdfd.log", true);

  sinks_.push_back(console_sink);
  sinks_.push_back(file_sink);

  logger_ =
      std::make_shared<spdlog::logger>("main", sinks_.begin(), sinks_.end());

  logger_->set_level(spdlog::level::trace);

  spdlog::set_pattern("[%H:%M:%S.%e] [%^%l%$] %v");

  atexit([]() {
    Logger::GetLogger()->flush();
    spdlog::shutdown();
  });
}

void Logger::AddSink(spdlog::sink_ptr sink) {
  logger_->sinks().push_back(sink);
}

auto Logger::GetLogger() -> std::shared_ptr<spdlog::logger> & {
  return logger_;
}
