#include <dfd_editor/CreateNewNodePopup.h>

#include <logging/Logger.h>

void CreateNewNodePopup::DrawContents() {
  if (ImGui::MenuItem("Date Process")) {
    Logger::Trace("[CreateNewNodePopup {}] MenuItem {} Clicked", canvas_id_,
        "Date Process");
    SignalHandel::Instance().create_new_node_(canvas_id_, "DataProcess", pos_);
  }
  if (ImGui::MenuItem("External Entity")) {
    Logger::Trace("[CreateNewNodePopup {}] MenuItem {} Clicked", canvas_id_,
        "External Entity");
    SignalHandel::Instance().create_new_node_(
        canvas_id_, "ExternalEntity", pos_);
  }
  if (ImGui::MenuItem("Data Store")) {
    Logger::Trace("[CreateNewNodePopup {}] MenuItem {} Clicked", canvas_id_,
        "Data Store");
    SignalHandel::Instance().create_new_node_(canvas_id_, "DataStorage", pos_);
  }
}
