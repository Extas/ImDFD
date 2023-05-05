#include <dfd_editor/NotificationWindow.h>
#include <logging/Logger.h>

NotificationWindow::NotificationWindow()
    : BaseWindow("Notifications"), sink_(new NotificationWindowSink(this)) {
  log_.Clear();
  Logger::AddSink(sink_);
}

void NotificationWindow::AddNotification(const std::string &message) {
  log_.AddLog(message.c_str());
}

void NotificationWindow::DrawContents() {
  log_.Draw(GetTitle().c_str(), GetIsOpenPtr());
}

void NotificationWindowSink::sink_it_(const spdlog::details::log_msg &msg) {
  spdlog::memory_buf_t formatted;
  formatter_->format(msg, formatted);
  auto formatted_msg = fmt::to_string(formatted);
  window_->AddNotification(formatted_msg);
}
