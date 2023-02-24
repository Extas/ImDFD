#include "ImGuiWindowsInterface.h"
#include <imgui_node_editor.h>
namespace ed = ax::NodeEditor;

class NodeEditerDemo : public ImGuiWindowsInterface {
private:
  ed::EditorContext *kMContext;

public:
  NodeEditerDemo(/* args */);
  ~NodeEditerDemo();

  void Update() override;
};

NodeEditerDemo::NodeEditerDemo(/* args */)
    : ImGuiWindowsInterface("NodeEditerDemo") {
  kMContext = ed::CreateEditor();
}

NodeEditerDemo::~NodeEditerDemo() {
  ed::DestroyEditor(kMContext);
}

inline void NodeEditerDemo::Update() {
  // begin
  ImGui::Begin(kMName);
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
