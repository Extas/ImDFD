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
  SignalHandel::Instance().navigate_sub_diagram_onclick_(node_editor_id);
}

void DataProcessNode::SetProcessingContent(
    const std::string &new_processing_content) {
  GetDataProcessing().SetContent(new_processing_content);
}

void DataProcessNode::SetProcessName(const std::string &new_process_name) {

  SetName(new_process_name);
}

auto DataProcessNode::GetDataProcessing() const -> const DataProcessData & {
  return data_processing_;
}
auto DataProcessNode::GetDataProcessing() -> DataProcessData & {
  return data_processing_;
}
