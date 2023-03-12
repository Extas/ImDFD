#include "dfd_editor/node_model/Node.h"
#include <dfd_editor/NodeEditorWindow.h>
#include <dfd_editor/node_model/Link.h>
#include <imgui.h>
#include <imgui_node_editor.h>

#include <logging/Logger.h>
#include <memory>
#include <string>
#include <utility>

NodeEditorWindow::NodeEditorWindow(std::string title)
    : BaseWindow(std::move(title)) {
}

NodeEditorWindow::NodeEditorWindow() : NodeEditorWindow("NodeEditor") {
}

void NodeEditorWindow::demo() {
  m_NodeManager.AddNode("A", std::make_pair(10, 10));
  m_NodeManager.AddInputPin("A In");
  m_NodeManager.AddOutputPin("A Out");
  m_NodeManager.AddNode("B", std::make_pair(210, 60));
  m_NodeManager.AddInputPin("B In");
  m_NodeManager.AddOutputPin("B Out");
}

void NodeEditorWindow::DrawContents() {
  ed::SetCurrentEditor(GetContext());
  ed::Begin("My Editor", ImVec2(0.0, 0.0));

  if (IsFirstFrame()) {
    FirstFrame();
  }

  DrawNode();
  DrawLink();
  HandleInteractions();
  ed::End();
  ed::SetCurrentEditor(nullptr);
}

void NodeEditorWindow::DrawNode() {

  for (const auto &node : m_NodeManager.GetNodes()) {
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
    ed::Link(link.GetId(), link.GetOutputPinId(), link.GetInputPinId());
  }
}

void NodeEditorWindow::HandleInteractions() {
  // Handle creation action, returns true if editor want to create new object
  // (node or link)
  if (ed::BeginCreate()) {
    ed::PinId inputPinId;
    ed::PinId outputPinId;
    if (ed::QueryNewLink(&inputPinId, &outputPinId)) {
      // 如果编辑器想要在两个针脚之间创建新链接，QueryNewLink() 就会返回 true。

      // TODO(HandleInteractions):
      // 链接只能在两个有效的针脚之间创建，判断连接是否有意义。
      if (inputPinId && outputPinId) // both are valid, let's accept link
      {
        // 当用户释放鼠标按钮时，ed::AcceptNewItem() 返回 true。
        if (ed::AcceptNewItem()) {
          // 接受了新链接，添加到链接列表中。
          m_LinkManager.AddLink(inputPinId.Get(), outputPinId.Get());
          Logger::Trace("dfd_editor: Accepted new link");
          // Draw new link.
          DrawLink();
        }

        // 通过调用 ed::RejectNewItem() 拒绝这些节点之间的连接。
      }
    }
  }
  ed::EndCreate();
}

void NodeEditorWindow::HandleDelete() {
  if (ed::BeginDelete()) {
    // There may be many links marked for deletion, let's loop over them.
    ed::LinkId deletedLinkId;
    while (ed::QueryDeletedLink(&deletedLinkId)) {
      // If you agree that link can be deleted, accept deletion.
      if (ed::AcceptDeletedItem()) {
        // Then remove link from your data.
        for (auto &link : m_LinkManager.GetLinks()) {
          if (link.GetId() == deletedLinkId.Get()) {
            m_LinkManager.RemoveLink(link.GetId());
            break;
          }
        }
      }

      // You may reject link deletion by calling:
      // ed::RejectDeletedItem();
    }
  }
  ed::EndDelete(); // Wrap up deletion action
}

auto NodeEditorWindow::IsFirstFrame() -> bool {
  static bool isFirstFrame = true;
  if (isFirstFrame) {
    isFirstFrame = false;
    return true;
  }
  return false;
}

auto NodeEditorWindow::GetContext() -> ed::EditorContext * {
  static bool isInitialized = false;
  static ed::EditorContext *context = nullptr;
  if (isInitialized) {
    return context;
  }
  Logger::Trace("dfd_editor: Initializing NodeEditor context");
  context = ed::CreateEditor();
  isInitialized = true;
  return context;
}

void NodeEditorWindow::FirstFrame() {
  demo();
  for (const auto &node : m_NodeManager.GetNodes()) {
    ed::SetNodePosition(node.GetId(),
        ImVec2(node.GetPosition().first, node.GetPosition().second));
  }
  ed::NavigateToContent(0.0f);
}

NodeEditorWindow::~NodeEditorWindow() {
  ed::DestroyEditor(m_Context);
}
