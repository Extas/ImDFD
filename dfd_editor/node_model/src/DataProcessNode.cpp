#include <node_model/DataProcessNode.h>
void DataProcessNode::DrawCustomContent() const {
  ImGui::Text("Description: %s", GetDataProcessing().GetContent().c_str());
  ImGui::Text("Sub-DFD ID: %d", GetDataProcessing().GetSubDataFlowDiagramId());
  ImGui::Text(
      "Input Data Flows: %zu", GetDataProcessing().GetInputDataFlows().size());
  ImGui::Text("Output Data Flows: %zu",
      GetDataProcessing().GetOutputDataFlows().size());
}

void DataProcessNode::SetName(const std::string &new_name) {
  Node::SetName(new_name);
  GetDataProcessing().SetName(new_name);
}

void DataProcessNode::SetProcessingContent(
    const std::string &new_processing_content) {
  GetDataProcessing().SetContent(new_processing_content);
}
