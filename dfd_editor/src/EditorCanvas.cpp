#include "sigslot/signal.hpp"
#include <dfd_editor/EditorCanvas.h>

#include <imgui.h>
#include <imgui_node_editor.h>

#include <logging/Logger.h>

EditorCanvas::EditorCanvas(const std::shared_ptr<Dfd> &dfd)
    : BaseWindow(dfd->GetName()), canvas_id_(dfd->GetElementId()), dfd_(dfd) {

  ConnectSignals();
}

void EditorCanvas::AddLink(const std::shared_ptr<DataFlow> &data_flow_ptr) {
  auto from_node_id = data_flow_ptr->source_->GetElementId();
  auto to_node_id = data_flow_ptr->destination_->GetElementId();
  auto from_node = node_manager_.GetNode(from_node_id);
  auto to_node = node_manager_.GetNode(to_node_id);
  if (!from_node.has_value() || !to_node.has_value()) {
    Logger::Error("Data flow is not valid");
  }

  const auto &from_pins = from_node.value().get().GetOutputPins();
  const auto &to_pins = to_node.value().get().GetInputPins();
  if (from_pins.size() != 1 || to_pins.size() != 1) {
    Logger::Error("Data flow is not valid");
  }
  link_manager_.AddLink(
      data_flow_ptr->GetElementId(), from_pins[0].GetId(), to_pins[0].GetId());
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

  UpdateDrawData();

  if (IsFirstFrame()) {
    FirstFrame();
  }

  DrawNode();
  DrawLink();
  HandleInteractions();
  HandleDelete();

  HandleRightClick();

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
    ed::PinId to_pin_id;
    ed::PinId from_pin_id;
    if (ed::QueryNewLink(&from_pin_id, &to_pin_id)) {
      if (from_pin_id && to_pin_id) { // both are valid, let's accept link
        if (ed::AcceptNewItem()) {
          auto input_pin = node_manager_.GetInputPinById(to_pin_id.Get());
          auto output_pin = node_manager_.GetOutputPinById(from_pin_id.Get());
          if (!input_pin.has_value()) {
            input_pin = node_manager_.GetInputPinById(from_pin_id.Get());
            output_pin = node_manager_.GetOutputPinById(to_pin_id.Get());
          }
          if (!input_pin.has_value() || !output_pin.has_value()) {
            Logger::Warn("Input or output pin is not valid");
//            ed::RejectNewItem();
            return;
          }

          auto source_node =
              node_manager_.GetNodeByPinId(output_pin.value().get().GetId());
          auto destination_node =
              node_manager_.GetNodeByPinId(input_pin.value().get().GetId());

          if (!source_node.has_value() || !destination_node.has_value()) {
            Logger::Error("Source or destination node is not valid");
            return;
          }
          auto source_node_id = source_node.value().get().GetId();
          auto destination_node_id = destination_node.value().get().GetId();
          dfd_->AddDataFlow(
              "New Dataflow", source_node_id, destination_node_id);
        }
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
        dfd_->DeleteFlow(deleted_link_id.Get());
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
    Logger::Trace(
        "[EditorCanvas {}] Initializing EditorCanvas context", GetId());
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

void EditorCanvas::HandleRightClick() {
  auto open_popup_position = ImGui::GetMousePos();
  create_new_node_popup_.SetPosition(
      open_popup_position.x, open_popup_position.y);
  ed::Suspend();
  if (ed::ShowBackgroundContextMenu()) {
    Logger::Trace("[EditorCanvas {}] ShowBackgroundContextMenu", GetId());
    create_new_node_popup_.Open();
  }
  ed::Resume();

  ed::Suspend();
  create_new_node_popup_.Draw();
  ed::Resume();
}

void EditorCanvas::ConnectSignals() {
  SignalHandel::Instance().create_new_node_.connect(
      [this](int64_t canvas_id, const std::string &node_type,
          std::pair<float, float> pos) {
        if (canvas_id == GetId()) {
          auto new_node_id = dfd_->AddNode(node_type, pos);
          ed::SetNodePosition(new_node_id, ImVec2(pos.first, pos.second));
        }
      });
}

void EditorCanvas::UpdateDrawData() {
  node_manager_.ClearNodes();
  link_manager_.ClearLinks();

  for (const auto &kDataProcessPtr : dfd_->data_processes_) {
    auto data_process_node = node_manager_.AddDataProcessNode(
        kDataProcessPtr->GetElementId(), &kDataProcessPtr->name_,
        &kDataProcessPtr->position_, &kDataProcessPtr->process_description_,
        kDataProcessPtr->sub_dfd_->GetElementId());

    SignalHandel::Instance().create_new_dfd_(kDataProcessPtr->sub_dfd_);
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
    AddLink(kDataFlowPtr);
  }
}
