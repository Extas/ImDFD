#include <dfd_editor/InfoWindow.h>
void Info::LoadNode(const std::shared_ptr<DfdNode> &node) {
  if (node) {
    name_ = std::ref(node->name_);
    description_ = std::ref(node->description_);
    if (auto data_process = std::dynamic_pointer_cast<DataProcess>(node)) {
    }
  }
}
void Info::LoadLink(const std::shared_ptr<DataFlow> &link) {
  if (link) {
    name_ = link->name_;
    description_ = link->description_;
  }
}
void Info::LoadElement(const std::shared_ptr<Element> &element) {
  current_element_ = element;
  if (current_element_) {
    if (auto node = std::dynamic_pointer_cast<DfdNode>(current_element_)) {
      LoadNode(node);
    } else if (auto link =
                   std::dynamic_pointer_cast<DataFlow>(current_element_)) {
      LoadLink(link);
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

InfoWindow::InfoWindow() : BaseWindow("Info") {
  SignalHandel::Instance().selected_node_.connect([this](int64_t node_id) {
    auto node = dfd_->GetNodeById(node_id);
    if (node) {
      info_.LoadElement(node);
    }
  });

  SignalHandel::Instance().selected_link_.connect([this](int64_t link_id) {
    auto link = dfd_->GetFlowById(link_id);
    if (link) {
      info_.LoadElement(link);
    }
  });
}
void InfoWindow::DrawContents() {
  DrawEditableTextValue(info_.GetName(), "Name:");
  ImGui::Separator();
  DrawTextValue(info_.GetDescription(), "Description:");
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
void InfoWindow::DrawEditableTextValue(
    std::optional<std::reference_wrapper<std::string>> text,
    const std::string &label) {
  static bool editing = false;
  static char buffer[128];

  if (!editing) {
    if (!DrawTextValue(text, label)) {
      return;
    }

    ImGui::SameLine();
    if (ImGui::Button("Edit")) {
      editing = true;
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
      editing = false;
      text.value().get() = std::string(buffer);
    }
  }
}
void InfoWindow::LoadDfd(const std::shared_ptr<Dfd> &dfd) {
  dfd_ = dfd;
}
