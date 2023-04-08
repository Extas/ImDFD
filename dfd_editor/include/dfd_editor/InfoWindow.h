#ifndef IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_INFOWINDOW_H_
#define IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_INFOWINDOW_H_

#include <dfd_model/DataFlow.h>
#include <dfd_model/DataItem.h>
#include <dfd_model/DataProcess.h>
#include <dfd_model/DataStorage.h>
#include <dfd_model/Dfd.h>
#include <dfd_model/DfdNode.h>
#include <dfd_model/Element.h>
#include <dfd_model/ExternalEntity.h>
#include <imgui.h>
#include <signal/SignalHandel.h>
#include <ui/BaseWindow.h>

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

class Info {
public:
  Info() = default;

  void LoadNode(const std::shared_ptr<DfdNode> &node) {
    if (node) {
      name_ = std::ref(node->name_);
      description_ = std::ref(node->description_);
      if (auto data_process = std::dynamic_pointer_cast<DataProcess>(node)) {
      }
    }
  }

  void LoadLink(const std::shared_ptr<DataFlow> &link) {
    if (link) {
      name_ = link->name_;
      description_ = link->description_;
    }
  }

  void LoadElement(const std::shared_ptr<Element> &element) {
    if (element) {
      if (auto node = std::dynamic_pointer_cast<DfdNode>(element)) {
        LoadNode(node);
      } else if (auto link = std::dynamic_pointer_cast<DataFlow>(element)) {
        LoadLink(link);
      }
    }
  }

  [[nodiscard]] auto GetName()
      -> std::optional<std::reference_wrapper<std::string>> {
    return name_;
  }

  [[nodiscard]] auto GetDescription()
      -> std::optional<std::reference_wrapper<std::string>> {
    return description_;
  }

private:
  std::optional<std::reference_wrapper<std::string>> name_;
  std::optional<std::reference_wrapper<std::string>> description_;
};

class InfoWindow : public BaseWindow {
public:
  explicit InfoWindow() : BaseWindow("Info") {
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

  void DrawContents() override {
    DrawEditableTextValue(info_.GetName(), "Name:");
    ImGui::Separator();
    DrawTextValue(info_.GetDescription(), "Description:");
  }

  static auto DrawTextValue(
      const std::optional<std::string> &text, const std::string &label = "") -> bool {

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

  void DrawEditableTextValue(
      std::optional<std::reference_wrapper<std::string>> text,
      const std::string &label = "") {
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

  void LoadDfd(const std::shared_ptr<Dfd> &dfd) {
    dfd_ = dfd;
  }

private:
  std::shared_ptr<Dfd> dfd_;
  Info info_;
};

#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_INFOWINDOW_H_
