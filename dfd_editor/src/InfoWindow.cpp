#include <dfd_editor/InfoWindow.h>
#include <string>

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
  DrawEditableTextValue(info_.GetDescription(), "Description:");
  if (info_.has_data_items_) {
    DrawDataItems(info_.GetDataItems());
  }

  if (!info_.GetInFlows().empty()) {
    for(auto flows : info_.GetInFlows()) {
      ImGui::Text("InFlows");
      ImGui::Text(flows.lock()->GetName().value().get().c_str());
    }
  }
  if (!info_.GetOutFlows().empty()) {
    for(auto flows : info_.GetOutFlows()) {
      ImGui::Text("OutFlows");
      ImGui::Text(flows.lock()->GetName().value().get().c_str());
    }
  }
}

void InfoWindow::DrawDataItems(std::vector<std::shared_ptr<DataItem>> &items) {
  ImGui::Text("Data Items:");

  ImGui::SameLine();
  if (ImGui::Button("Detail##")) {
    data_item_popup_.SetDataFlow(info_.GetElement());
    data_item_popup_.Open();
  }
  data_item_popup_.Draw();

  for (const auto &kDataItem : items) {
    ImGui::Indent();
    ImGui::BulletText("%s", kDataItem->GetName().value().get().c_str());
    ImGui::SameLine();
    ImGui::Text(
        "Type: %s", kDataItem->GetDateTypeName().value().get().c_str());
    ImGui::Unindent();
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

    auto button_name = "Edit##" + label + text.value().get();
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
    ImGui::InputText("##editable_text", buffer, sizeof(buffer));

    if (ImGui::Button("OK")) {
      editing_state = false;
      text.value().get() = std::string(buffer);
    }
  }
  ImGui::Separator();
}
auto InfoWindow::DrawTextValue(
    const std::optional<std::string> &text, const std::string &label) -> bool {

  if (text.has_value()) {
    if (!label.empty()) {
      auto new_label = label.substr(0, label.find("##"));
      ImGui::Text("%s", new_label.c_str());
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
      has_data_items_ = true;
      data_items_ = data_store->stored_data_items_;
    } else if (auto data_flow = std::dynamic_pointer_cast<DataFlow>(node)) {
    }
    inflows_ = node->input_data_flows_;
    outflows_ = node->output_data_flows_;
  }
}
void Info::LoadLink(const std::shared_ptr<DataFlow> &link) {
  if (link) {
    name_ = link->name_;
    has_data_items_ = true;
    data_items_ = link->data_items_;
  }
}
void Info::LoadElement(const std::shared_ptr<Element> &element) {
  current_element_ = element;
  has_data_items_ = false;
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
auto Info::GetDataItems() -> std::vector<std::shared_ptr<DataItem>> & {
  return data_items_;
}
auto Info::GetElement() -> std::shared_ptr<Element> {
  return current_element_;
}
auto Info::GetInFlows() -> std::vector<std::weak_ptr<DataFlow>> {
  return inflows_;
}
auto Info::GetOutFlows() -> std::vector<std::weak_ptr<DataFlow>> {
  return outflows_;
}
void InfoWindow::LoadDfd(const std::shared_ptr<Dfd> &dfd) {
  dfd_ = dfd;
}
