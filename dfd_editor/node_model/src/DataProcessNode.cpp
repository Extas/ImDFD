#include <node_model/DataProcessNode.h>
void DataProcessNode::DrawCustomContent() const {
  ImGui::Text("Description: %s", GetDataProcessing().GetDescription().c_str());
  ImGui::Text("Sub-DFD ID: %d", GetDataProcessing().GetSubDataFlowDiagramId());
  ImGui::Text(
      "Input Data Flows: %zu", GetDataProcessing().GetInputDataFlows().size());
  ImGui::Text("Output Data Flows: %zu",
      GetDataProcessing().GetOutputDataFlows().size());
}
