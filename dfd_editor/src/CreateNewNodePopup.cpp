#include <dfd_editor/CreateNewNodePopup.h>

#include <logging/Logger.h>

void CreateNewNodePopup::DrawContents() {
  if (ImGui::MenuItem("Date Process")) {
    Logger::Trace("[CreateNewNodePopup] Create Date Process");
  }
  if (ImGui::MenuItem("Output Action")) {
  }
}
