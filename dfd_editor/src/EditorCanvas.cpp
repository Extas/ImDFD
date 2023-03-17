#include <dfd_editor/EditorCanvas.h>

#include <imgui.h>
#include <imgui_node_editor.h>

#include <logging/Logger.h>
#include <string>
#include <utility>

EditorCanvas::EditorCanvas(std::string title)
    : BaseWindow(std::move(title)), canvas_id_(GetNewCanvasId()) {
}

EditorCanvas::EditorCanvas() : EditorCanvas("EditorCanvas") {
}

void EditorCanvas::Demo() {
  node_manager_.AddNode("A", std::make_pair(10, 10));
  node_manager_.AddInputPin("A In");
  node_manager_.AddOutputPin("A Out");
  node_manager_.AddNode("B", std::make_pair(210, 60));
  node_manager_.AddInputPin("B In");
  node_manager_.AddOutputPin("B Out");
  node_manager_.AddDataProcessNode("C", std::make_pair(410, 10));
}

void EditorCanvas::DrawContents() {
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

void EditorCanvas::DrawNode() const {
  for (const auto &kNode : node_manager_.GetNodes()) {
    kNode->Draw();
  }
}

void EditorCanvas::DrawLink() {
  for (const auto &kLink : link_manager_.GetLinks()) {
    ed::Link(kLink.GetId(), kLink.GetOutputPinId(), kLink.GetInputPinId());
  }
}

void EditorCanvas::HandleInteractions() {
  // Handle creation action, returns true if editor want to create new object
  // (node or link)
  if (ed::BeginCreate()) {
    ed::PinId input_pin_id;
    ed::PinId output_pin_id;
    if (ed::QueryNewLink(&input_pin_id, &output_pin_id)) {
      // 如果编辑器想要在两个针脚之间创建新链接，QueryNewLink() 就会返回 true。

      // TODO(HandleInteractions):
      // 链接只能在两个有效的针脚之间创建，判断连接是否有意义。
      if (input_pin_id && output_pin_id) // both are valid, let's accept link
      {
        // 当用户释放鼠标按钮时，ed::AcceptNewItem() 返回 true。
        if (ed::AcceptNewItem()) {
          // 接受了新链接，添加到链接列表中。
          link_manager_.AddLink(input_pin_id.Get(), output_pin_id.Get());
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

void EditorCanvas::HandleDelete() {
  if (ed::BeginDelete()) {
    // There may be many links marked for deletion, let's loop over them.
    ed::LinkId deleted_link_id;
    while (ed::QueryDeletedLink(&deleted_link_id)) {
      // If you agree that link can be deleted, accept deletion.
      if (ed::AcceptDeletedItem()) {
        // Then remove link from your data.
        for (const auto &kLink : link_manager_.GetLinks()) {
          if (kLink.GetId() == deleted_link_id.Get()) {
            link_manager_.RemoveLink(kLink.GetId());
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

auto EditorCanvas::IsFirstFrame() -> bool {
  if (is_first_frame_) {
    is_first_frame_ = false;
    return true;
  }
  return false;
}

void EditorCanvas::FirstFrame() {
  Demo();
  for (const auto &kNode : node_manager_.GetNodes()) {
    ed::SetNodePosition(kNode->GetId(),
        ImVec2(kNode->GetPosition().first, kNode->GetPosition().second));
  }
  ed::NavigateToContent(0.0F);
}

void EditorCanvas::SetCanvasCallback(
    std::function<void(int canvas_id)> navigate_to_canvas_callback,
    std::function<int(std::string title)> create_new_canvas_callback) {
  node_manager_.navigate_to_editor_callback_ =
      std::move(navigate_to_canvas_callback);
  node_manager_.get_new_editor_id_callback_ =
      std::move(create_new_canvas_callback);
}

auto EditorCanvas::GetContext() -> ed::EditorContext * {
  if (context_ == nullptr) {
    Logger::Trace("dfd_editor: Initializing EditorCanvas context");
    context_ = ed::CreateEditor();
  }
  return context_;
}

auto EditorCanvas::GetNewCanvasId() -> int {
  static int node_editor_id = 0;
  return node_editor_id++;
}

auto EditorCanvas::GetId() const -> int {
  return canvas_id_;
}

EditorCanvas::~EditorCanvas() {
  ed::DestroyEditor(context_);
}
