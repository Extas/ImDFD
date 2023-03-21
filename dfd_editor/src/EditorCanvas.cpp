#include <dfd_editor/EditorCanvas.h>

#include <imgui.h>
#include <imgui_node_editor.h>

#include <logging/Logger.h>

EditorCanvas::EditorCanvas(const std::shared_ptr<Dfd> &dfd)
    : BaseWindow(dfd->name_), canvas_id_(dfd->GetElementId()), dfd_(dfd) {
  // 一共五个元素
  // DataFlow
  // DataItem 不画
  // DataProcess AddDataProcessNode
  // ExternalEntity AddDataProcessNode
  // DataStorage  AddDataProcessNode
  for (const auto &kDataProcessPtr : dfd_->data_processes_) {
    node_manager_.AddDataProcessNode(kDataProcessPtr->GetElementId(),
        &kDataProcessPtr->name_, &kDataProcessPtr->position_,
        &kDataProcessPtr->process_description_, kDataProcessPtr->sub_dfd_);
  }
  for (const auto &kExternalEntityPtr : dfd_->external_entities_) {
    node_manager_.AddExternalEntityNode(kExternalEntityPtr->GetElementId(),
        &kExternalEntityPtr->name_, &kExternalEntityPtr->position_);
  }
  for (const auto &kDataStoragePtr : dfd_->data_storages_) {
    node_manager_.AddDataStorageNode(kDataStoragePtr->GetElementId(),
        &kDataStoragePtr->name_, &kDataStoragePtr->position_);
  }
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

          // DrawCustom new link.
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
  for (const auto &kNode : node_manager_.GetNodes()) {
    ed::SetNodePosition(kNode->GetId(),
        ImVec2(kNode->GetPosition().first, kNode->GetPosition().second));
  }
  ed::NavigateToContent(0.0F);
}

auto EditorCanvas::GetContext() -> ed::EditorContext * {
  if (context_ == nullptr) {
    Logger::Trace("dfd_editor: Initializing EditorCanvas context");
    context_ = ed::CreateEditor();
  }
  return context_;
}

auto EditorCanvas::GetId() const -> int64_t {
  return canvas_id_;
}

EditorCanvas::~EditorCanvas() {
  ed::DestroyEditor(context_);
}
