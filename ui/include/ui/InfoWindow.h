#include <imgui.h>
#include <ui/BaseWindow.h>

#include <string>
#include <vector>

// 定义元素信息类
class ElementInfo {
public:
  std::string name;
  std::string description;
  std::vector<std::string> data_items;
  std::vector<std::string> input_streams;
  std::vector<std::string> output_streams;

  // 默认构造函数
  ElementInfo() {
  }

  // 构造函数，传入元素名称和描述
  ElementInfo(const std::string &name, const std::string &description)
      : name(name), description(description) {
  }
};

// 定义信息窗口类
class InfoWindow : public BaseWindow {
public:
  // 构造函数，传入元素信息类的引用
  InfoWindow(ElementInfo &info) : BaseWindow("Info"), info(info) {
  }

  void DrawContents() override {

    // 显示元素名称和描述
    ImGui::Text("%s", info.name.c_str());
    ImGui::Separator();
    ImGui::Text("%s", info.description.c_str());

    // 显示数据项列表
    if (!info.data_items.empty()) {
      ImGui::Separator();
      ImGui::Text("Data Items:");
      for (auto &item : info.data_items) {
        ImGui::Text("- %s", item.c_str());
      }
    }

    // 显示输入数据流列表
    if (!info.input_streams.empty()) {
      ImGui::Separator();
      ImGui::Text("Input Streams:");
      for (auto &stream : info.input_streams) {
        ImGui::Text("- %s", stream.c_str());
      }
    }

    // 显示输出数据流列表
    if (!info.output_streams.empty()) {
      ImGui::Separator();
      ImGui::Text("Output Streams:");
      for (auto &stream : info.output_streams) {
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
    if (!info.name.empty()) {
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
  ElementInfo &info;
};
