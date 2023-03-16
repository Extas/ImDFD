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

void NotificationWindow::DrawContents() {
  if (ImGui::SmallButton("[Debug] Add 5 entries")) {
    static int counter = 0;
    const char *categories[3] = {"info", "warn", "error"};
    const char *words[] = {"Bumfuzzled", "Cattywampus", "Snickersnee",
        "Abibliophobia", "Absquatulate", "Nincompoop", "Pauciloquent"};
    for (int n = 0; n < 5; n++) {
      const char *category = categories[counter % IM_ARRAYSIZE(categories)];
      const char *word = words[counter % IM_ARRAYSIZE(words)];
      log_.AddLog(
          "[%05d] [%s] Hello, current time is %.1f, here's a word: '%s'\n",
          ImGui::GetFrameCount(), category, ImGui::GetTime(), word);
      counter++;
    }
  }
  log_.Draw(GetTitle().c_str(), GetIsOpenPtr());
}
