#include <ui/BaseWindow.h>

#include <logging/Logger.h>

BaseWindow::BaseWindow(std::string title) : title_(std::move(title)) {
}

BaseWindow::BaseWindow() : BaseWindow("Untitled") {
}

void BaseWindow::DrawContents() {
}

void BaseWindow::Draw() {
  if (!ImGui::Begin(title_.c_str(), &is_open_)) {
    ImGui::End();
    return;
  }

  DrawContents();

  ImGui::End();
}
