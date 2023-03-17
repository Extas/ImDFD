#include <node_model/DataProcessNode.h>

void DataProcessNode::DrawCustomContent() const {
  ImGui::Text("Description: %s", GetDataProcessing().GetContent().c_str());
  ImGui::Text("Sub-DFD ID: %d", GetDataProcessing().GetSubDataFlowDiagramId());
  ImGui::Text(
      "Input Data Flows: %zu", GetDataProcessing().GetInputDataFlows().size());
  ImGui::Text("Output Data Flows: %zu",
      GetDataProcessing().GetOutputDataFlows().size());

  if (ImGui::Button("Navigate to Sub Data Flow Diagram")) {
    NavigateToNodeEditorById(data_processing_.GetSubDataFlowDiagramId());
  }
}

void DataProcessNode::NavigateToNodeEditorById(int node_editor_id) const {
  if (navigate_to_node_editor_callback_) {
    navigate_to_node_editor_callback_(node_editor_id);
  }
}

void DataProcessNode::SetNavigateToNodeEditorCallback(
    std::function<void(int)> navigate_to_node_editor_callback) {
  navigate_to_node_editor_callback_ =
      std::move(navigate_to_node_editor_callback);
}

void DataProcessNode::SetProcessingContent(
    const std::string &new_processing_content) {
  GetDataProcessing().SetContent(new_processing_content);
}

void DataProcessNode::SetProcessName(const std::string &new_process_name) {

  SetName(new_process_name);
}

auto DataProcessNode::GetDataProcessing() const -> const DataProcess & {
  return data_processing_;
}
auto DataProcessNode::GetDataProcessing() -> DataProcess & {
  return data_processing_;
}
