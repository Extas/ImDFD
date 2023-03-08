#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <imgui.h>
#include <string>

class BaseWindow {
public:
  BaseWindow();
  explicit BaseWindow(std::string title);

  virtual ~BaseWindow() = default;

  // Override this method in derived classes to add your own window content
  virtual void DrawContents() {
  }

  // Show the window
  void Show();

  BaseWindow(BaseWindow &&) = delete;
  BaseWindow(const BaseWindow &) = delete;
  auto operator=(BaseWindow &&) -> BaseWindow & = delete;
  auto operator=(const BaseWindow &) -> BaseWindow & = delete;

private:
  std::string m_Title;
  bool m_IsOpen = false;
};

#endif // BASEWINDOW_H
