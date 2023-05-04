#include <dfd_editor/EditorCanvas.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_node_editor.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>
#include <logging/Logger.h>

EditorCanvas::EditorCanvas(const std::shared_ptr<Dfd> &dfd)
    : BaseWindow(dfd->GetName()), canvas_id_(dfd->GetElementId()), dfd_(dfd) {

  ConnectSignals();
}

void EditorCanvas::DrawContents() {
  ed::SetCurrentEditor(GetOrInitContext());
  ed::Begin("My Editor", ImVec2(0.0, 0.0));

  LoadDrawData();

  if (IsFirstFrame()) {
    FirstFrame();
  }

  DrawNode();
  DrawLink();

  HandleInteractions();
  HandleDelete();

  UpdateSelected();

  Navigate();

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
  HandleRightClick();
  HandleCreateNewLink();
}
void EditorCanvas::HandleCreateNewLink() {
  // (node or link)
  if (ed::BeginCreate()) {
    ed::PinId to_pin_id;
    ed::PinId from_pin_id;
    if (ed::QueryNewLink(&from_pin_id, &to_pin_id)) {
      if (from_pin_id && to_pin_id) { // both are valid, let's accept link
        auto input_pin = node_manager_.GetInputPinById(to_pin_id.Get());
        auto output_pin = node_manager_.GetOutputPinById(from_pin_id.Get());
        if (!output_pin.has_value()) {
          input_pin = node_manager_.GetInputPinById(from_pin_id.Get());
          output_pin = node_manager_.GetOutputPinById(to_pin_id.Get());
        }
        if (!input_pin.has_value() || !output_pin.has_value()) {
          auto showLabel = [](const char *label, ImColor color) {
            ImGui::SetCursorPosY(
                ImGui::GetCursorPosY() - ImGui::GetTextLineHeight());
            auto size = ImGui::CalcTextSize(label);

            auto padding = ImGui::GetStyle().FramePadding;
            auto spacing = ImGui::GetStyle().ItemSpacing;

            ImGui::SetCursorPos(
                ImGui::GetCursorPos() + ImVec2(spacing.x, -spacing.y));

            auto rectMin = ImGui::GetCursorScreenPos() - padding;
            auto rectMax = ImGui::GetCursorScreenPos() + size + padding;

            auto drawList = ImGui::GetWindowDrawList();
            drawList->AddRectFilled(rectMin, rectMax, color, size.y * 0.15f);
            ImGui::TextUnformatted(label);
          };
          showLabel("x Incompatible Pin Kind", ImColor(45, 32, 32, 180));
          ed::RejectNewItem();
        } else if (ed::AcceptNewItem()) {
          auto source_node =
              node_manager_.GetNodeByPinId(output_pin.value().get().GetId());
          auto destination_node =
              node_manager_.GetNodeByPinId(input_pin.value().get().GetId());

          if (!source_node.has_value() || !destination_node.has_value()) {
            Logger::Error("[EditorCanvas {}] Invalid node", GetId());
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
    ed::NodeId node_id = 0;
    while (ed::QueryDeletedNode(&node_id)) {
      if (ed::AcceptDeletedItem()) {
        dfd_->DeleteNode(node_id.Get());
      }
    }
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

auto EditorCanvas::GetOrInitContext() -> ed::EditorContext * {
  if (context_ == nullptr) {
    config_.UserPointer = this;
    config_.SaveNodeSettings = [](ed::NodeId node_id, const char *data,
                                   size_t size, ed::SaveReasonFlags reason,
                                   void *user_pointer) -> bool {
      auto *self = static_cast<EditorCanvas *>(user_pointer);
      auto node = self->dfd_->GetNodeById(node_id.Get());
      auto pos = ed::GetNodePosition(node_id);
      node->SetPosition(pos.x, pos.y);
      Logger::Trace("[EditorCanvas {}] Saved position of node({})",
          self->GetId(), node_id.Get());
      return true;
    };
    Logger::Trace("[EditorCanvas {}] First open", GetId());
    context_ = ed::CreateEditor(&config_);
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
  create_new_node_list_popup_.SetPosition(
      open_popup_position.x, open_popup_position.y);
  ed::Suspend();
  if (ed::ShowNodeContextMenu(&context_node_id_)) {
    Logger::Trace("[EditorCanvas {}] Show Node Context Menu", GetId());
    delete_node_popup_.Open();
  } else if (ed::ShowLinkContextMenu(&context_link_id_)) {
    Logger::Trace("[EditorCanvas {}] Show Link Context Menu", GetId());
    delete_link_popup_.Open();
  } else if (ed::ShowBackgroundContextMenu()) {
    Logger::Trace("[EditorCanvas {}] Show Background Context Menu", GetId());
    create_new_node_list_popup_.Open();
  }
  ed::Resume();

  ed::Suspend();
  delete_link_popup_.Draw();
  delete_node_popup_.Draw();
  create_new_node_list_popup_.Draw();
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

  SignalHandel::Instance().navigate_element_onclick_.connect(
      [this](int64_t element_id) { NavigateToElement(element_id); });
}

void EditorCanvas::LoadDrawData() {
  node_manager_.ClearNodes();
  link_manager_.ClearLinks();

  LoadDataProcessNodes();
  LoadExternalEntityNodes();
  LoadDataStorageNodes();
  LoadDataFlowLinks();
}
void EditorCanvas::LoadDataFlowLinks() {
  for (const auto &kDataFlowPtr : dfd_->data_flows_) {
    auto from_node_id = kDataFlowPtr->source_->GetElementId();
    auto to_node_id = kDataFlowPtr->destination_->GetElementId();
    auto from_node = node_manager_.GetNodeById(from_node_id);
    auto to_node = node_manager_.GetNodeById(to_node_id);
    if (!from_node.has_value() || !to_node.has_value()) {
      Logger::Error("Data flow is not valid");
    }

    const auto &from_pins = from_node.value().get().GetOutputPins();
    const auto &to_pins = to_node.value().get().GetInputPins();
    if (from_pins.size() != 1 || to_pins.size() != 1) {
      Logger::Error("Data flow is not valid");
    }
    link_manager_.AddLink(
        kDataFlowPtr->GetElementId(), from_pins[0].GetId(), to_pins[0].GetId());
  }
}
void EditorCanvas::LoadDataStorageNodes() {
  for (const auto &kDataStoragePtr : dfd_->data_storages_) {
    auto data_storage_node =
        node_manager_.AddDataStorageNode(kDataStoragePtr->GetElementId(),
            kDataStoragePtr->GetName(), kDataStoragePtr->GetPosition());
  }
}
void EditorCanvas::LoadExternalEntityNodes() {
  for (const auto &kExternalEntityPtr : dfd_->external_entities_) {
    auto external_entity_node =
        node_manager_.AddExternalEntityNode(kExternalEntityPtr->GetElementId(),
            kExternalEntityPtr->GetName(), kExternalEntityPtr->GetPosition());
  }
}
void EditorCanvas::LoadDataProcessNodes() {
  for (const auto &kDataProcessPtr : dfd_->data_processes_) {
    auto data_process_node = node_manager_.AddDataProcessNode(
        kDataProcessPtr->GetElementId(), kDataProcessPtr->GetName(),
        kDataProcessPtr->GetPosition(), kDataProcessPtr->GetDescription(),
        kDataProcessPtr->sub_dfd_->GetElementId());

    SignalHandel::Instance().create_new_dfd_(kDataProcessPtr->sub_dfd_);
  }
}

void EditorCanvas::UpdateSelected() {
  static unsigned int last_selected_id = 0;
  selected_nodes_.resize(ed::GetSelectedObjectCount());
  selected_links_.resize(ed::GetSelectedObjectCount());
  int node_count = ed::GetSelectedNodes(
      selected_nodes_.data(), static_cast<int>(selected_nodes_.size()));
  int link_count = ed::GetSelectedLinks(
      selected_links_.data(), static_cast<int>(selected_links_.size()));

  selected_nodes_.resize(node_count);
  selected_links_.resize(link_count);

  if (selected_nodes_.size() == 1) {
    const auto kSelectedId = selected_nodes_[0].Get();
    if (last_selected_id != kSelectedId) {
      last_selected_id = kSelectedId;
      SignalHandel::Instance().selected_node_(kSelectedId);
    }
  } else if (selected_links_.size() == 1) {
    const auto kSelectedId = selected_links_[0].Get();
    if (last_selected_id != kSelectedId) {
      last_selected_id = kSelectedId;
      SignalHandel::Instance().selected_link_(kSelectedId);
      Logger::Trace("[EditorCanvas {}] Selected link {}", GetId(), kSelectedId);
    }
  }
}

void EditorCanvas::NavigateToElement(uint64_t element_id) {
  navigate_id_ = element_id;
  need_navigate_ = true;
}

void EditorCanvas::ResetZoom() {
  ed::NavigateToContent();
}

void EditorCanvas::Navigate() {
  if (need_navigate_) {
    auto node = node_manager_.GetNodeById(navigate_id_);
    if (node.has_value()) {
      ed::SelectNode(ed::NodeId(navigate_id_), false);
    } else {
      ed::SelectLink(ed::LinkId(navigate_id_), false);
    }
    ed::NavigateToSelection();
    need_navigate_ = false;
  }
}
