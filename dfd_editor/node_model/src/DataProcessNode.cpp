#include <node_model/DataProcessNode.h>

void DataProcessNode::DrawCustomContent() const {
  ImGui::Text("Description: %s", GetDataProcessing().GetContent().c_str());
  ImGui::Text("Sub-DFD ID: %d", GetDataProcessing().GetSubDataFlowDiagramId());
  ImGui::Text(
      "Input Data Flows: %zu", GetDataProcessing().GetInputDataFlows().size());
  ImGui::Text("Output Data Flows: %zu",
      GetDataProcessing().GetOutputDataFlows().size());

  if (ImGui::Button("Open Data Flow Diagram")) {
    if (open_dfd_callback_) {
      open_dfd_callback_();
    }
  }
}

void DataProcessNode::SetProcessingContent(
    const std::string &new_processing_content) {
  GetDataProcessing().SetContent(new_processing_content);
}

void DataProcessNode::SetOpenDFDCallback(
    std::function<void()> open_dfd_callback) {
  open_dfd_callback_ = std::move(open_dfd_callback);
}

void DataProcessNode::SetProcessName(const std::string &new_process_name) {

  SetName(new_process_name);
}
