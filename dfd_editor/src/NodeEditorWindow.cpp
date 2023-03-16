#include <dfd_editor/NodeEditorWindow.h>

#include <imgui.h>
#include <logging/Logger.h>

NodeEditorWindow::NodeEditorWindow(std::string title)
    : BaseWindow(std::move(title)) {
}

void NodeEditorWindow::DrawContents() {
  if (ImGui::BeginTabBar("NodeEditorTabBar")) {
    for (auto &node_editor : node_editors_) {
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
}
