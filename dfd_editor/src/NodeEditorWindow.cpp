#include <dfd_editor/NodeEditorWindow.h>

#include <imgui.h>
#include <logging/Logger.h>

NodeEditorWindow::NodeEditorWindow(std::string title)
    : BaseWindow(std::move(title)) {
}

void NodeEditorWindow::DrawContents() {
  if (ImGui::BeginTabBar("NodeEditorTabBar")) {
    // 不要用范围 for 循环遍历，读取的引用不正确
    for (size_t i = 0; i < node_editors_.size(); ++i) {
      std::shared_ptr<NodeEditor> &node_editor = node_editors_[i];
      std::string tab_label = node_editor->GetTitle();
      if (ImGui::BeginTabItem(tab_label.c_str())) {
        node_editor->DrawContents();
        ImGui::EndTabItem();
      }
    }
    ImGui::EndTabBar();
  }
}

void NodeEditorWindow::AddNodeEditor(
    const std::shared_ptr<NodeEditor> &node_editor) {
  Logger::Trace("Adding node editor to window");
  node_editors_.push_back(node_editor);
  node_editors_.back()->SetNodeManagerCallback([self = shared_from_this()]() {
    std::static_pointer_cast<NodeEditorWindow>(self)
        ->CreateNewDataFlowDiagram();
  });
}

void NodeEditorWindow::CreateNewDataFlowDiagram() {
  AddNodeEditor(std::make_shared<NodeEditor>("New Data Flow Diagram"));
}
