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
  std::string title_;
  bool is_open_ = false;

public:
  [[nodiscard]] auto GetTitle() const -> const std::string & {
    return title_;
  }

  void SetTitle(const std::string &title) {
    title_ = title;
  }

  auto GetIsOpenPtr() -> bool * {
    return &is_open_;
  }

  [[nodiscard]] auto IsOpen() const -> bool {
    return is_open_;
  }

  void Close() {
    is_open_ = false;
  }

  void Open() {
    is_open_ = true;
  }

  void Toggle() {
    is_open_ = !is_open_;
  }

  BaseWindow(BaseWindow &&other) noexcept
      : title_(std::move(other.title_)), is_open_(other.is_open_) {
  }
  BaseWindow(const BaseWindow &) = delete;
  auto operator=(BaseWindow &&) -> BaseWindow & = delete;
  auto operator=(const BaseWindow &) -> BaseWindow & = delete;
};

#endif // BASEWINDOW_H
