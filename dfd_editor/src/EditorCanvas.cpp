#include <dfd_editor/EditorCanvas.h>

#include <imgui.h>
#include <imgui_node_editor.h>

#include <logging/Logger.h>
#include <string>

EditorCanvas::EditorCanvas(const std::shared_ptr<Dfd> &dfd)
    : BaseWindow(dfd->name_), canvas_id_(dfd->GetElementId()), dfd_(dfd) {
  for (const auto &kDataProcessPtr : dfd_->data_processes_) {
    auto data_process_node =
        node_manager_.AddDataProcessNode(kDataProcessPtr->GetElementId(),
            &kDataProcessPtr->name_, &kDataProcessPtr->position_,
            &kDataProcessPtr->process_description_, kDataProcessPtr->sub_dfd_);
  }
  for (const auto &kExternalEntityPtr : dfd_->external_entities_) {
    auto external_entity_node =
        node_manager_.AddExternalEntityNode(kExternalEntityPtr->GetElementId(),
            &kExternalEntityPtr->name_, &kExternalEntityPtr->position_);
  }
  for (const auto &kDataStoragePtr : dfd_->data_storages_) {
    auto data_storage_node =
        node_manager_.AddDataStorageNode(kDataStoragePtr->GetElementId(),
            &kDataStoragePtr->name_, &kDataStoragePtr->position_);
  }
  for (const auto &kDataFlowPtr : dfd_->data_flows_) {
    Connect(kDataFlowPtr);
  }
}

void EditorCanvas::Connect(const std::shared_ptr<DataFlow> &kDataFlowPtr) {
  auto from_node = node_manager_.GetNode(kDataFlowPtr->source_->GetElementId());
  auto to_node =
      node_manager_.GetNode(kDataFlowPtr->destination_->GetElementId());
  if (!from_node.has_value() || !to_node.has_value()) {
    Logger::Error("Data flow is not valid");
  }

  const auto& from_pins = from_node.value().get().GetOutputPins();
  const auto& to_pins = to_node.value().get().GetInputPins();
  if (from_pins.size() != 1 || to_pins.size() != 1) {
    Logger::Error("Data flow is not valid");
  }
  link_manager_.AddLink(from_pins[0].GetId(), to_pins[0].GetId());
}

void EditorCanvas::AddPin(const std::shared_ptr<DfdNode> &dfd_model_ptr,
    const std::shared_ptr<Node> &node) {
  for (const auto &kOutputPin : dfd_model_ptr->output_data_flows_) {
    if (kOutputPin.expired()) {
      Logger::Error("Output pin is expired");
      continue;
    }
    auto output_pin_ptr = kOutputPin.lock();
    node->AddOutputPin(output_pin_ptr->GetElementId(), &output_pin_ptr->name_);
  }
  for (const auto &kInputPin : dfd_model_ptr->input_data_flows_) {
        if (kInputPin.expired()) {
          Logger::Error("Input pin is expired");
          continue;
        }
        auto input_pin_ptr = kInputPin.lock();
        node->AddInputPin(input_pin_ptr->GetElementId(), &input_pin_ptr->name_);
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
      if (input_pin_id && output_pin_id) // both are valid, let's accept link
      {
        if (ed::AcceptNewItem()) {
          link_manager_.AddLink(input_pin_id.Get(), output_pin_id.Get());
          Logger::Trace("[EditorCanvas] Accepted new link");

          // DrawCustom new link.
          DrawLink();
        }

        // ed::RejectNewItem()
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
            Logger::Trace("[EditorCanvas] Accepted deleted link");
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
    Logger::Trace("[EditorCanvas] Initializing EditorCanvas context");
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
