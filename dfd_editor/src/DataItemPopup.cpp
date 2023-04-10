#include <dfd_editor/DataItemPopup.h>
#include <dfd_model/DataFlow.h>
#include <imgui_stdlib.h>
#include <ui/Widgets.h>

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
  for (auto it = data_json.begin(); it != data_json.end(); ++it) {
    imdfd::ui::widgets::DrawTextWithLabel(
        it.value()["value"].get<std::string>(), it.key());
  }
  ImGui::Unindent();

  ImGui::Text("Used By Data Flows: ");
  ImGui::Indent();
  for (const auto &data_flow : data_item->GetDataFlows()) {
    ImGui::BulletText("%s", data_flow->GetName().value().get().c_str());
  }
  ImGui::Unindent();

  auto sub_data_items = data_item->GetSubDataItems();
  if (!sub_data_items.empty()) {
    static bool is_expanded = false; // 控制展开状态的变量
    ImGui::Text("Sub Data Items: ");
    ImGui::SetNextItemWidth(100);
    ImGui::Checkbox("Expand", &is_expanded); // 展开控件
    ImGui::Indent();
    if (is_expanded) { // 如果展开了，则显示所有子数据项
      for (const auto &sub_data_item : sub_data_items) {
        auto sub_data_item_name = sub_data_item->GetName().value().get();
        DrawDataItem(sub_data_item);
      }
    } else { // 否则只显示子数据项的名称
      for (const auto &sub_data_item : sub_data_items) {
        auto sub_data_item_name = sub_data_item->GetName().value().get();
        ImGui::Text("%s", sub_data_item_name.c_str());
      }
    }
    ImGui::Unindent();
  }

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
