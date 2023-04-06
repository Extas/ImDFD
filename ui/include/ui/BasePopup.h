#ifndef IMDFD_UI_INCLUDE_UI_BASEPOPUP_H_
#define IMDFD_UI_INCLUDE_UI_BASEPOPUP_H_

#include <imgui.h>
#include <string>

class BasePopup {
public:
  BasePopup();
  explicit BasePopup(std::string title);

  virtual ~BasePopup() = default;

  virtual void DrawContents() = 0;

  virtual void Draw();

private:
  std::string title_;
  bool is_open_ = false;

public:
  void Close() {
    is_open_ = false;
  }

  void Open() {
    ImGui::OpenPopup(title_.c_str());
  }

  void Toggle() {
    is_open_ = !is_open_;
  }

  BasePopup(BasePopup &&other) noexcept
      : title_(std::move(other.title_)), is_open_(other.is_open_) {
  }
  BasePopup(const BasePopup &) = delete;
  auto operator=(BasePopup &&) -> BasePopup & = delete;
  auto operator=(const BasePopup &) -> BasePopup & = delete;
};

#endif // IMDFD_UI_INCLUDE_UI_BASEPOPUP_H_
