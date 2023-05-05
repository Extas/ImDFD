#include <ui/BasePopup.h>

#include <logging/Logger.h>

BasePopup::BasePopup(std::string title) : title_(std::move(title)) {
}

BasePopup::BasePopup() : BasePopup("Untitled") {
}

void BasePopup::Draw() {
  if (ImGui::BeginPopup(title_.c_str())) {
    DrawContents();
    ImGui::EndPopup();
  }
}
