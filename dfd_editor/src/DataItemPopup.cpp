#include "imgui.h"
#include <dfd_editor/DataItemPopup.h>
#include <dfd_model/DataFlow.h>
#include <signal/SignalHandel.h>
#include <string>
#include <ui/Widgets.h>
#include <vector>

// 在DataItemPopup.cpp中实现
DataItemPopup::DataItemPopup() : BasePopup("Data Items") {
}

void DataItemPopup::DrawContents() {
  DrawDataItems();
  DrawAddDataItemButton();

  if (ImGui::Button("Close")) {
    ImGui::CloseCurrentPopup();
  }
}

void DataItemPopup::Draw() {
  if (ImGui::BeginPopupModal(
          GetTitle().c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
    DrawContents();
    ImGui::EndPopup();
  }
}

void DataItemPopup::DrawDataItems() {
  if (data_items_ == nullptr) {
    return;
  }

  for (const auto &data_item : *data_items_) {
    DrawDataItem(data_item);
  }
}

void DataItemPopup::DrawDataItem(std::shared_ptr<DataItem> data_item) {
  ImGui::PushID(data_item->GetElementId());
  imdfd::ui::widgets::DrawInputText(
      data_item->GetName().value().get(), "Name: ");
  imdfd::ui::widgets::DrawInputText(
      data_item->GetDateTypeName().value().get(), "Data Type: ");

  ImGui::Text("Data Definitions: ");
  ImGui::Indent();
  nlohmann::json data_json = data_item->GetDataJson();
  std::map<std::string, std::pair<std::string, std::string>> updates;
  std::vector<std::string> keys_to_remove;
  int id = 0;
  for (auto it = data_json.begin(); it != data_json.end(); ++it) {
    auto data_definition = it.key();
    auto original_data_definition = data_definition;
    imdfd::ui::widgets::DrawInputText(
        data_definition, "Data Def: " + std::to_string(id));
    ImGui::SameLine();
    auto data_value = it.value()["value"].get<std::string>();
    auto original_data_value = data_value;
    imdfd::ui::widgets::DrawInputText(
        data_value, "Value: " + std::to_string(id));
    ImGui::SameLine();
    std::string button_label = "Delete " + std::to_string(id);
    if (ImGui::Button(button_label.c_str())) {
      keys_to_remove.push_back(original_data_definition);
    }
    id++;

    if (data_definition != original_data_definition ||
        data_value != original_data_value) {
      updates[original_data_definition] =
          std::make_pair(data_definition, data_value);
    }
  }
  ImGui::Unindent();

  // 应用更改
  for (const auto &update : updates) {
    if (update.first != update.second.first) {
      data_json[update.second.first] = data_json[update.first];
      data_json.erase(update.first);
    }
    data_json[update.second.first]["value"] = update.second.second;
  }
  // 删除选定的 Data Definitions
  for (const auto &key : keys_to_remove) {
    data_json.erase(key);
  }

  if (ImGui::Button("Add Data Definition")) {
    std::string new_key = "new_key";
    int counter = 1;
    while (data_json.contains(new_key)) {
      new_key = "new def " + std::to_string(counter);
      counter++;
    }
    data_json[new_key] = {{"type", "default type"}, {"value", "default value"}};
  }
  data_item->SetDataJson(data_json);

  ImGui::Text("Used By Data Flows: ");
  ImGui::Indent();
  for (const auto &data_flow : data_item->GetDataFlows()) {
    //    ImGui::BulletText("%s", data_flow->GetName().value().get().c_str());
    if (ImGui::Button(data_flow->GetName().value().get().c_str())) {
      SignalHandel::Instance().navigate_element_onclick_(
          data_flow->GetElementId());
      ImGui::CloseCurrentPopup();
    }
  }

  ImGui::Unindent();

  //  auto sub_data_items = data_item->GetSubDataItems();
  //  if (!sub_data_items.empty()) {
  //    static bool is_expanded = false; // 控制展开状态的变量
  //    ImGui::Text("Sub Data Items: ");
  //    ImGui::SetNextItemWidth(100);
  //    ImGui::SameLine();
  //    ImGui::Checkbox("Expand", &is_expanded); // 展开控件
  //    ImGui::Indent();
  //    if (is_expanded) { // 如果展开了，则显示所有子数据项
  //      for (const auto &sub_data_item : sub_data_items) {
  //        auto sub_data_item_name = sub_data_item->GetName().value().get();
  //        DrawDataItem(sub_data_item);
  //      }
  //    } else { // 否则只显示子数据项的名称
  //      for (const auto &sub_data_item : sub_data_items) {
  //        auto sub_data_item_name = sub_data_item->GetName().value().get();
  //        ImGui::Text("%s", sub_data_item_name.c_str());
  //      }
  //    }
  //    ImGui::Unindent();
  //  }

  ImGui::PopID();
  ImGui::Separator();
}

void DataItemPopup::LoadDataItems(
    std::vector<std::shared_ptr<DataItem>> &data_items) {
  data_items_ = &data_items;
}

void DataItemPopup::DrawAddDataItemButton() {
  if (ImGui::Button("Add Data Item")) {
  }
}
