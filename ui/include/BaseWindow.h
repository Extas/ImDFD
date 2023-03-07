#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <string>
#include <imgui.h>

class BaseWindow {
public:
  BaseWindow(const std::string& title, const ImVec2& size);
  virtual ~BaseWindow() = default;

  // Override this method in derived classes to add your own window content
  virtual void DrawContents() {}

  // Show the window
  void Show();

protected:
  std::string m_Title;
  ImVec2 m_Size;
  bool m_IsOpen = false;
};

#endif // BASEWINDOW_H
