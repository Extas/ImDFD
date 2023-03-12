#include "dfd_editor/node_model/Link.h"
#include "imgui.h"
#include "imgui_node_editor.h"
#include <dfd_editor/NodeEditorWindow.h>
#include <logging/Logger.h>
#include <string>

NodeEditorWindow::NodeEditorWindow(std::string title)
    : BaseWindow(std::move(title)) {
}

NodeEditorWindow::NodeEditorWindow() : NodeEditorWindow("NodeEditor") {
}

void NodeEditorWindow::AddNodeObj(NodeObj &&nodeObj) {
  if (auto *node = dynamic_cast<Node *>(&nodeObj)) {
    m_Nodes.emplace_back(std::move(*node));
  } else {
    // TODO(NodeEditorWindow): Handle error: Unknown NodeObj type
  }
}

void NodeEditorWindow::demo() {
  Node nodeA("A", {10, 10});
  Node nodeB("B", {210, 60});
  nodeA.AddInputPin("A In");
  nodeA.AddOutputPin("A Out");
  nodeB.AddInputPin("B In");
  nodeB.AddOutputPin("B Out");
  AddNodeObj(std::move(nodeA));
  AddNodeObj(std::move(nodeB));
}

void NodeEditorWindow::DrawContents() {
  ed::SetCurrentEditor(GetContext());
  ed::Begin("My Editor", ImVec2(0.0, 0.0));

  if (IsFirstFrame()) {
    FirstFrame();
  }

  DrawNode();
  DrawLink();
  ed::End();
  ed::SetCurrentEditor(nullptr);
}

void NodeEditorWindow::DrawNode() {

  for (const auto &node : m_Nodes) {
    ed::BeginNode(node.GetId());
    ImGui::Text(node.GetName().c_str());
    for (const auto &pin : node.GetInputPins()) {
      ed::BeginPin(pin.GetId(), ed::PinKind::Input);
      ImGui::Text(pin.GetName().c_str());
      ed::EndPin();
      ImGui::SameLine();
    }
    for (const auto &pin : node.GetOutputPins()) {
      ed::BeginPin(pin.GetId(), ed::PinKind::Output);
      ImGui::Text(pin.GetName().c_str());
      ed::EndPin();
      ImGui::SameLine();
    }
    ed::EndNode();
  }
}

void NodeEditorWindow::DrawLink() {
  for (const auto &link : m_LinkManager.GetLinks()) {
    ed::Link(link.GetId(), link.GetOutputPin()->GetId(),
        link.GetInputPin()->GetId());
  }
}

void NodeEditorWindow::FirstFrame() {
  demo();
  for (auto &node : m_Nodes) {
    ed::SetNodePosition(node.GetId(),
        ImVec2(node.GetPosition().first, node.GetPosition().second));
  }
  ed::NavigateToContent(0.0f);
}

NodeEditorWindow::~NodeEditorWindow() {
  ed::DestroyEditor(m_Context);
}
