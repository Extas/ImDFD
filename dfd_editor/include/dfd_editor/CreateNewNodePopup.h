#ifndef IMDFD_DFD_EDITOR_INCLUDE_CREATENEWNODEPOPUP_H_
#define IMDFD_DFD_EDITOR_INCLUDE_CREATENEWNODEPOPUP_H_

#include <ui/BasePopup.h>

class CreateNewNodePopup : public BasePopup {
public:
  CreateNewNodePopup() : BasePopup("Create New Node") {
  }

  ~CreateNewNodePopup() override = default;

  void DrawContents() override;

  CreateNewNodePopup(CreateNewNodePopup &&other) noexcept
      : BasePopup(std::move(other)) {
  }
  CreateNewNodePopup(const CreateNewNodePopup &) = delete;
  auto operator=(CreateNewNodePopup &&) -> CreateNewNodePopup & = delete;
  auto operator=(const CreateNewNodePopup &) -> CreateNewNodePopup & = delete;
};

#endif // IMDFD_DFD_EDITOR_INCLUDE_CREATENEWNODEPOPUP_H_
