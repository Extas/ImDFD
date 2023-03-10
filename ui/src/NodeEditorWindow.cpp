#include <ui/NodeEditorWindow.h>

NodeEditerWindow::NodeEditerWindow(std::string title)
    : BaseWindow(std::move(title)) {
}

void NodeEditerWindow::DrawContents() {
  // begin
  ImGui::Begin(GetTitle().c_str());
  ed::SetCurrentEditor(kMContext);
  ed::Begin("My Editor", ImVec2(0.0, 0.0f));
  int uniqueId = 1;
  // Start drawing nodes.
  ed::BeginNode(uniqueId++);
  ImGui::Text("Node A");
  ed::BeginPin(uniqueId++, ed::PinKind::Input);
  ImGui::Text("-> In");
  ed::EndPin();
  ImGui::SameLine();
  ed::BeginPin(uniqueId++, ed::PinKind::Output);
  ImGui::Text("Out ->");
  ed::EndPin();
  ed::EndNode();
  ed::End();
  ed::SetCurrentEditor(nullptr);
  ImGui::End();
}

NodeEditerWindow::~NodeEditerWindow() {
  ed::DestroyEditor(kMContext);
}
