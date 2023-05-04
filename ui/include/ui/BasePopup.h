#ifndef IMDFD_UI_INCLUDE_UI_BASEPOPUP_H_
#define IMDFD_UI_INCLUDE_UI_BASEPOPUP_H_
#define IMGUI_DEFINE_MATH_OPERATORS

#include <imgui.h>
#include <signal/SignalHandel.h>
#include <string>
#include <ui/BasePopup.h>

class BasePopup {
public:
  BasePopup();
  explicit BasePopup(std::string title);

  virtual ~BasePopup() = default;


  virtual void DrawContents() = 0;

  virtual void Draw();

private:
  std::pair<float, float> pos_;
  std::string title_;
  bool is_open_ = false;


public:
  void SetPosition(float x, float y) {
    pos_ = {x, y};
  }

  [[nodiscard]] auto GetPosition() const -> std::pair<float, float> {
    return pos_;
  }

  [[nodiscard]] auto IsOpen() const -> bool {
    return is_open_;
  }

  [[nodiscard]] auto GetTitle() const -> const std::string & {
    return title_;
  }

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
