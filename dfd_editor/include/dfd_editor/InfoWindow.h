#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <imgui.h>
#include <ui/BaseWindow.h>

#include <string>
#include <utility>
#include <vector>

class ElementInfo {
public:
  std::string name_;
  std::string description_;
  std::vector<std::string> data_items_;
  std::vector<std::string> input_streams_;
  std::vector<std::string> output_streams_;

  ElementInfo() = default;

  ElementInfo(std::string name, std::string description)
      : name_(std::move(name)), description_(std::move(description)) {
  }
};

class InfoWindow : public BaseWindow {
public:
  explicit InfoWindow(ElementInfo &info)
      : BaseWindow("Info"), element_info_(info) {
  }

  void DrawContents() override {

    ImGui::Text("%s", element_info_.name_.c_str());
    ImGui::Separator();
    ImGui::Text("%s", element_info_.description_.c_str());

    if (!element_info_.data_items_.empty()) {
      ImGui::Separator();
      ImGui::Text("Data Items:");
      for (auto &item : element_info_.data_items_) {
        ImGui::Text("- %s", item.c_str());
      }
    }

    if (!element_info_.input_streams_.empty()) {
      ImGui::Separator();
      ImGui::Text("Input Streams:");
      for (auto &stream : element_info_.input_streams_) {
        ImGui::Text("- %s", stream.c_str());
      }
    }

    if (!element_info_.output_streams_.empty()) {
      ImGui::Separator();
      ImGui::Text("Output Streams:");
      for (auto &stream : element_info_.output_streams_) {
        ImGui::Text("- %s", stream.c_str());
      }
    }

    // if (!info.description.empty()) {
    //   ImGui::Separator();
    //   ImGui::Text("Description:");
    //   ImGui::InputTextMultiline("##Description", &info.description,
    //       ImVec2(-1.0f, ImGui::GetTextLineHeight() * 3));
    // }

    if (!element_info_.name_.empty()) {
      ImGui::Separator();
      ImGui::Text("Jump to:");
      if (ImGui::Button("Data Item Definition")) {
      }
      if (ImGui::Button("Input Stream Definition")) {
      }
      if (ImGui::Button("Output Stream Definition")) {
      }
    }
  }

private:
  ElementInfo element_info_;
};

#endif // INFOWINDOW_H
