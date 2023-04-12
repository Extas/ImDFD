#include <node_model/DataProcessNode.h>
#include <node_model/util/widgets.h>

void DataProcessNode::DrawCustomContent() const {

//  ImGui::Text("%s", data_processing_.GetDescription().c_str());
  ImGui::Spring(1, 0);
  std::string button_name = "Open Sub DFD##" + std::to_string(GetId());
  if (ImGui::Button(button_name.c_str())) {
    NavigateToNodeEditorById(data_processing_.GetSubDataFlowDiagramId());
  }
  ImGui::Spring(1, 0);
}

void DataProcessNode::NavigateToNodeEditorById(int64_t node_editor_id) {
  SignalHandel::Instance().navigate_sub_diagram_onclick_(node_editor_id);
}

void DataProcessNode::SetProcessingContent(
    const std::string &new_processing_content) {
  data_processing_.SetContent(new_processing_content);
}

void DataProcessNode::SetProcessName(std::string *new_process_name) {

  SetName(new_process_name);
}

auto DataProcessNode::GetDataProcessing() -> DataProcessData & {
  return data_processing_;
}
auto DataProcessNode::GetDataProcessing() const -> const DataProcessData & {
  return data_processing_;
}
