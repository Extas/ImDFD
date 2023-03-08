#include "BaseWindow.h"

BaseWindow::BaseWindow(std::string title) : m_Title(std::move(title)) {
}

BaseWindow::BaseWindow() : BaseWindow("Untitled") {
}

void BaseWindow::DrawContents() {
}

void BaseWindow::Show() {
  if (!ImGui::Begin(m_Title.c_str(), &m_IsOpen)) {
    ImGui::End();
    return;
  }

  DrawContents();

  ImGui::End();
}
