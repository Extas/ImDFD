#ifndef IMDFD_DFD_EDITOR_INCLUDE_CREATENEWNODEPOPUP_H_
#define IMDFD_DFD_EDITOR_INCLUDE_CREATENEWNODEPOPUP_H_

#include <signal/SignalHandel.h>
#include <ui/BasePopup.h>

class CreateNewNodePopup : public BasePopup {
public:
  CreateNewNodePopup(int64_t canvas_id)
      : BasePopup("Create New Node"), canvas_id_(canvas_id) {
  }

  ~CreateNewNodePopup() override = default;

  void DrawContents() override;

  void SetPosition(float x, float y) {
    pos_ = {x, y};
  }

  CreateNewNodePopup(CreateNewNodePopup &&other) noexcept
      : BasePopup(std::move(other)), canvas_id_(other.canvas_id_) {
  }
  CreateNewNodePopup(const CreateNewNodePopup &) = delete;
  auto operator=(CreateNewNodePopup &&) -> CreateNewNodePopup & = delete;
  auto operator=(const CreateNewNodePopup &) -> CreateNewNodePopup & = delete;

private:
  int64_t canvas_id_{};
  std::pair<float, float> pos_;
};

#endif // IMDFD_DFD_EDITOR_INCLUDE_CREATENEWNODEPOPUP_H_
