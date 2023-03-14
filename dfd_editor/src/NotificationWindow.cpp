#include <dfd_editor/NotificationWindow.h>

NotificationWindow::NotificationWindow() : BaseWindow("Notifications") {
  log_.Clear();
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-vararg"
void NotificationWindow::AddInfoNotification(const std::string &message) {
  Notification notification = {
      NotificationType::INFO, message, std::chrono::system_clock::now()};
  log_.AddLog("[INFO][%lld] %s\n",
      std::chrono::system_clock::to_time_t(notification.timestamp),
      notification.message.c_str());
}

void NotificationWindow::AddWarningNotification(const std::string &message) {
  Notification notification = {
      NotificationType::WARNING, message, std::chrono::system_clock::now()};
  log_.AddLog("[WARNING][%lld] %s\n",
      std::chrono::system_clock::to_time_t(notification.timestamp),
      notification.message.c_str());
}

void NotificationWindow::AddErrorNotification(const std::string &message) {
  Notification notification = {
      NotificationType::ERROR, message, std::chrono::system_clock::now()};
  log_.AddLog("[ERROR][%lld] %s\n",
      std::chrono::system_clock::to_time_t(notification.timestamp),
      notification.message.c_str());
}
#pragma clang diagnostic pop

void NotificationWindow::Show() {
  log_.Draw(GetTitle().c_str(), GetIsOpenPtr());
}
