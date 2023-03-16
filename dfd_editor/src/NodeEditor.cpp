#include <dfd_editor/NodeEditor.h>

#include <imgui.h>
#include <imgui_node_editor.h>

#include <logging/Logger.h>
#include <string>
#include <utility>

NodeEditor::NodeEditor(std::string title) : BaseWindow(std::move(title)) {
}

NodeEditor::NodeEditor() : NodeEditor("NodeEditor") {
}

void NodeEditor::Demo() {
  node_manager_.AddNode("A", std::make_pair(10, 10));
  node_manager_.AddInputPin("A In");
  node_manager_.AddOutputPin("A Out");
  node_manager_.AddNode("B", std::make_pair(210, 60));
  node_manager_.AddInputPin("B In");
  node_manager_.AddOutputPin("B Out");
  node_manager_.AddDataProcessNode("C", std::make_pair(410, 10), DataProcess{});
}

void NodeEditor::DrawContents() {
  ed::SetCurrentEditor(GetContext());
  ed::Begin("My Editor", ImVec2(0.0, 0.0));

  if (IsFirstFrame()) {
    FirstFrame();
  }

  DrawNode();
  DrawLink();
  HandleInteractions();
  HandleDelete();

  ed::End();
  ed::SetCurrentEditor(nullptr);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-vararg"
void NodeEditor::DrawNode() {

  for (const auto &node : node_manager_.GetNodes()) {
    node->Draw();
  }
}
#pragma clang diagnostic pop

void NodeEditor::DrawLink() {
  for (const auto &link : link_manager_.GetLinks()) {
    ed::Link(link.GetId(), link.GetOutputPinId(), link.GetInputPinId());
  }
}

void NodeEditor::HandleInteractions() {
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
          link_manager_.AddLink(inputPinId.Get(), outputPinId.Get());
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

void NodeEditor::HandleDelete() {
  if (ed::BeginDelete()) {
    // There may be many links marked for deletion, let's loop over them.
    ed::LinkId deletedLinkId;
    while (ed::QueryDeletedLink(&deletedLinkId)) {
      // If you agree that link can be deleted, accept deletion.
      if (ed::AcceptDeletedItem()) {
        // Then remove link from your data.
        for (const auto &link : link_manager_.GetLinks()) {
          if (link.GetId() == deletedLinkId.Get()) {
            link_manager_.RemoveLink(link.GetId());
            Logger::Trace("dfd_editor: Accepted deleted link");
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

auto NodeEditor::IsFirstFrame() -> bool {
  if (is_first_frame_) {
    is_first_frame_ = false;
    return true;
  }
  return false;
}

auto NodeEditor::GetContext() -> ed::EditorContext * {
  if (context_ == nullptr) {
    Logger::Trace("dfd_editor: Initializing NodeEditor context");
    context_ = ed::CreateEditor();
  }
  return context_;
}

void NodeEditor::FirstFrame() {
  Demo();
  for (const auto &node : node_manager_.GetNodes()) {
    ed::SetNodePosition(node->GetId(),
        ImVec2(node->GetPosition().first, node->GetPosition().second));
  }
  ed::NavigateToContent(0.0f);
}

NodeEditor::~NodeEditor() {
  ed::DestroyEditor(context_);
}

void NodeEditor::SetActive(bool active) {
  active_ = active;
}