#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <imgui.h>
#include <string>

class BaseWindow {
public:
  BaseWindow();
  explicit BaseWindow(std::string title);

  virtual ~BaseWindow() = default;

  virtual void DrawContents();

  virtual void Draw();

private:
  std::string m_Title;
  bool m_IsOpen = false;

public:
  [[nodiscard]] auto GetTitle() const -> const std::string & {
    return m_Title;
  }

  void SetTitle(const std::string &title) {
    m_Title = title;
  }

  bool *GetIsOpenPtr() {
    return &m_IsOpen;
  }

  [[nodiscard]] auto IsOpen() const -> bool {
    return m_IsOpen;
  }

  void Close() {
    m_IsOpen = false;
  }

  void Open() {
    m_IsOpen = true;
  }

  void Toggle() {
    m_IsOpen = !m_IsOpen;
  }

  BaseWindow(BaseWindow &&other) noexcept
      : m_Title(std::move(other.m_Title)), m_IsOpen(other.m_IsOpen) {
  }
  BaseWindow(const BaseWindow &) = delete;
  auto operator=(BaseWindow &&) -> BaseWindow & = delete;
  auto operator=(const BaseWindow &) -> BaseWindow & = delete;
};

#endif // BASEWINDOW_H
