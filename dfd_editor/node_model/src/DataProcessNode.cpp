#include <node_model/DataProcessNode.h>
#include <node_model/util/widgets.h>

void DataProcessNode::DrawCustomContent() const {

  ImGui::Spring(1, 0);
  std::string button_name = "Open Sub DFD##" + std::to_string(GetId());
  if (ImGui::Button(button_name.c_str())) {
    NavigateToNodeEditorById(sub_data_flow_diagram_id_);
  }
  ImGui::Spring(1, 0);
}

void DataProcessNode::NavigateToNodeEditorById(int64_t node_editor_id) {
  SignalHandel::Instance().navigate_sub_diagram_onclick_(node_editor_id);
}
