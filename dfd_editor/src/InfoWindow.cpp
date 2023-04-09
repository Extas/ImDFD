#include <dfd_editor/InfoWindow.h>
InfoWindow::InfoWindow() : BaseWindow("Info") {
  SignalHandel::Instance().selected_node_.connect([this](int64_t node_id) {
    auto node = dfd_->GetNodeById(node_id);
    if (node) {
      Info new_info;
      info_ = new_info;
      info_.LoadElement(node);
    }
  });

  SignalHandel::Instance().selected_link_.connect([this](int64_t link_id) {
    auto link = dfd_->GetFlowById(link_id);
    if (link) {
      Info new_info;
      info_ = new_info;
      info_.LoadElement(link);
    }
  });
}

void InfoWindow::DrawContents() {
  DrawEditableTextValue(info_.GetName(), "Name:");
  ImGui::Separator();

  DrawEditableTextValue(info_.GetDescription(), "Description:");
  ImGui::Separator();

  DrawDataItems(info_.GetDataItems());
}
void InfoWindow::DrawDataItems(
    const std::vector<std::shared_ptr<DataItem>> &items) {
  ImGui::Text("Data Items:");
  for (const auto &kDataItem : items) {
    DrawEditableTextValue(kDataItem->GetName(), "Name:");
  }
}
void InfoWindow::DrawEditableTextValue(
    std::optional<std::reference_wrapper<std::string>> text,
    const std::string &label) {
  static std::unordered_map<std::string, bool> editing;
  static char buffer[128];

  auto &editing_state = editing[label];

  if (!editing_state) {
    if (!DrawTextValue(text, label)) {
      return;
    }

    auto button_name = "Edit##" + label;
    if (ImGui::Button(button_name.c_str())) {
      editing_state = true;
      if (text.has_value()) {
        strncpy(buffer, text.value().get().c_str(), sizeof(buffer));
        buffer[sizeof(buffer) - 1] = '\0';
      } else {
        buffer[0] = '\0';
      }
    }
  } else {
    ImGui::Text("%s", label.c_str());
    ImGui::SameLine();
    ImGui::InputText("##editable_text", buffer, sizeof(buffer));

    if (ImGui::Button("OK")) {
      editing_state = false;
      text.value().get() = std::string(buffer);
    }
  }
}
auto InfoWindow::DrawTextValue(
    const std::optional<std::string> &text, const std::string &label) -> bool {

  if (text.has_value()) {
    if (!label.empty()) {
      ImGui::Text("%s", label.c_str());
    }
    ImGui::SameLine();
    ImGui::Text("%s", text.value().c_str());
    return true;
  }
  return false;
}

void Info::LoadNode(const std::shared_ptr<DfdNode> &node) {
  if (node) {
    name_ = std::ref(node->name_);
    if (auto data_process = std::dynamic_pointer_cast<DataProcess>(node)) {
      description_ = std::ref(node->description_);
    } else if (auto data_store = std::dynamic_pointer_cast<DataStorage>(node)) {
      data_items_ = data_store->stored_data_items_;
    } else if (auto data_flow = std::dynamic_pointer_cast<DataFlow>(node)) {
    }
  }
}
void Info::LoadLink(const std::shared_ptr<DataFlow> &link) {
  if (link) {
    name_ = link->name_;
    data_items_ = link->data_items_;
  }
}
void Info::LoadElement(const std::shared_ptr<Element> &element) {
  current_element_ = element;
  if (current_element_) {
    if (auto link = std::dynamic_pointer_cast<DataFlow>(current_element_)) {
      LoadLink(link);
    } else if (auto node =
                   std::dynamic_pointer_cast<DfdNode>(current_element_)) {
      LoadNode(node);
    }
  }
}

auto Info::GetName() -> std::optional<std::reference_wrapper<std::string>> {
  return name_;
}
auto Info::GetDescription()
    -> std::optional<std::reference_wrapper<std::string>> {
  return description_;
}
auto Info::GetDataItems() -> std::vector<std::shared_ptr<DataItem>> {
  return data_items_;
}
void InfoWindow::LoadDfd(const std::shared_ptr<Dfd> &dfd) {
  dfd_ = dfd;
}
