#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <imgui.h>
#include <ui/BaseWindow.h>

#include <string>
#include <utility>
#include <vector>

// 定义元素信息类
class ElementInfo {
public:
  std::string name_;
  std::string description_;
  std::vector<std::string> data_items_;
  std::vector<std::string> input_streams_;
  std::vector<std::string> output_streams_;

  // 默认构造函数
  ElementInfo() = default;

  // 构造函数，传入元素名称和描述
  ElementInfo(std::string name, std::string description)
      : name_(std::move(name)), description_(std::move(description)) {
  }
};

// 定义信息窗口类
class InfoWindow : public BaseWindow {
public:
  // 构造函数，传入元素信息类的引用
  explicit InfoWindow(ElementInfo &info)
      : BaseWindow("Info"), element_info_(info) {
  }

  void DrawContents() override {

    // 显示元素名称和描述
    ImGui::Text("%s", element_info_.name_.c_str());
    ImGui::Separator();
    ImGui::Text("%s", element_info_.description_.c_str());

    // 显示数据项列表
    if (!element_info_.data_items_.empty()) {
      ImGui::Separator();
      ImGui::Text("Data Items:");
      for (auto &item : element_info_.data_items_) {
        ImGui::Text("- %s", item.c_str());
      }
    }

    // 显示输入数据流列表
    if (!element_info_.input_streams_.empty()) {
      ImGui::Separator();
      ImGui::Text("Input Streams:");
      for (auto &stream : element_info_.input_streams_) {
        ImGui::Text("- %s", stream.c_str());
      }
    }

    // 显示输出数据流列表
    if (!element_info_.output_streams_.empty()) {
      ImGui::Separator();
      ImGui::Text("Output Streams:");
      for (auto &stream : element_info_.output_streams_) {
        ImGui::Text("- %s", stream.c_str());
      }
    }

    // // 显示可操作的文本框
    // if (!info.description.empty()) {
    //   ImGui::Separator();
    //   ImGui::Text("Description:");
    //   ImGui::InputTextMultiline("##Description", &info.description,
    //       ImVec2(-1.0f, ImGui::GetTextLineHeight() * 3));
    // }

    // 显示可跳转的按钮
    if (!element_info_.name_.empty()) {
      ImGui::Separator();
      ImGui::Text("Jump to:");
      if (ImGui::Button("Data Item Definition")) {
        // 跳转到数据项定义窗口
      }
      if (ImGui::Button("Input Stream Definition")) {
        // 跳转到输入数据流定义窗口
      }
      if (ImGui::Button("Output Stream Definition")) {
        // 跳转到输出数据流定义窗口
      }
    }
  }

private:
  ElementInfo element_info_;
};

#endif // INFOWINDOW_H
