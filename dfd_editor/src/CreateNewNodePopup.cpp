#include <dfd_editor/CreateNewNodePopup.h>

#include <logging/Logger.h>

void CreateNewNodePopup::DrawContents() {
  auto cur_pos_imv2 = ImGui::GetCursorPos();
  auto cur_pos = std::make_pair(cur_pos_imv2.x, cur_pos_imv2.y);

  if (ImGui::MenuItem("Date Process")) {
    Logger::Trace("[CreateNewNodePopup] MenuItem {} Clicked", "Date Process");
    SignalHandel::Instance().create_new_node_("DataProcess", cur_pos);
  }
  if (ImGui::MenuItem("External Entity")) {
    Logger::Trace(
        "[CreateNewNodePopup] MenuItem {} Clicked", "External Entity");
  }
  if (ImGui::MenuItem("Data Store")) {
    Logger::Trace("[CreateNewNodePopup] MenuItem {} Clicked", "Data Store");
  }
}
