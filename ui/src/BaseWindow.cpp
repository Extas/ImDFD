#include "BaseWindow.h"

BaseWindow::BaseWindow(const std::string &title, const ImVec2 &size)
    : m_Title(title), m_Size(size) {
}

void BaseWindow::Show() {
  ImGui::SetNextWindowSize(m_Size, ImGuiCond_FirstUseEver);
  if (!ImGui::Begin(m_Title.c_str(), &m_IsOpen)) {
    ImGui::End();
    return;
  }

  DrawContents();

  ImGui::End();
}
