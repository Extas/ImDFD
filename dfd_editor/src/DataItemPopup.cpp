#include "imgui.h"
#include <dfd_editor/DataItemPopup.h>
#include <dfd_model/DataFlow.h>
#include <signal/SignalHandel.h>
#include <string>
#include <ui/Widgets.h>
#include <utility>
#include <vector>

DataItemPopup::DataItemPopup() : BasePopup("Data Items") {
}

void DataItemPopup::DrawContents() {
  std::vector<std::shared_ptr<DataItem>> data_items;
  if (std::dynamic_pointer_cast<DataFlow>(element_) != nullptr) {
    data_items = std::dynamic_pointer_cast<DataFlow>(element_)->data_items_;
  }
  if (std::dynamic_pointer_cast<DataStorage>(element_) != nullptr) {
    data_items =
        std::dynamic_pointer_cast<DataStorage>(element_)->GetDataItems();
  }
  // data_item find id same
  auto data_item = std::find_if(
      data_items.begin(), data_items.end(), [this](const auto &data_item) {
        return data_item->GetElementId() == data_item_id_;
      });

  DrawDataItem(*data_item);

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

void DataItemPopup::DrawDataItem(const std::shared_ptr<DataItem> &data_item) {
  ImGui::PushID(data_item->GetElementId());

  imdfd::ui::widgets::DrawInputText(
      data_item->GetName().value().get(), "Name: ");
  imdfd::ui::widgets::DrawInputText(
      data_item->GetDateTypeName().value().get(), "Data Type: ");

  ImGui::Separator();
  ImGui::Text("Data Definitions: ");

  nlohmann::json data_json = data_item->GetDataJson();
  static std::map<std::string, std::pair<std::string, std::string>> updates;
  updates.clear();
  static std::vector<std::string> keys_to_remove;
  keys_to_remove.clear();

  auto column_names = std::vector<std::string>{"Definition", "Value"};

  // Initialize rowData
  static std::vector<std::pair<std::string, std::string>> originalData;
  originalData.clear();
  originalData.reserve(data_json.size());

  static std::vector<std::pair<std::string, std::string>> updatedData;
  updatedData.clear();
  updatedData.reserve(data_json.size());

  static std::vector<std::vector<std::reference_wrapper<std::string>>> rowData;
  rowData.clear();
  rowData.reserve(data_json.size());
  for (auto it = data_json.begin(); it != data_json.end(); ++it) {
    auto data_definition = it.key();
    auto data_value = it.value()["value"].get<std::string>();

    originalData.emplace_back(data_definition, data_value);
    updatedData.emplace_back(
        originalData.back().first, originalData.back().second);
    rowData.push_back({updatedData.back().first, updatedData.back().second});
  }

  // Prepare action callbacks
  std::map<std::string, std::function<void(int)>> action_callbacks;
  action_callbacks["Delete"] = [&](int rowIndex) {
    auto it = data_json.begin();
    std::advance(it, rowIndex);
    keys_to_remove.push_back(it.key());
  };

  // Draw the custom table
  imdfd::ui::widgets::DrawCustomTable(column_names, rowData, action_callbacks);

  // Apply updates
  for (size_t i = 0; i < rowData.size(); ++i) {
    const auto &original = originalData[i];
    const auto &updated = rowData[i];

    if (original.first != updated[0].get() ||
        original.second != updated[1].get()) {
      if (original.first != updated[0].get()) {
        data_json[updated[0].get()] = data_json[original.first];
        data_json.erase(original.first);
      }
      data_json[updated[0].get()]["value"] = updated[1].get();
    }
  }

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

  ImGui::Separator();
  ImGui::Text("Used By Data Flows: ");
  ImGui::Indent();
  for (const auto &data_flow : data_item->GetDataFlows()) {
    if (ImGui::Button(data_flow->GetName().get().c_str())) {
      SignalHandel::Instance().navigate_element_onclick_(
          data_flow->GetElementId());
      ImGui::CloseCurrentPopup();
    }
  }

  ImGui::Unindent();

  if (std::dynamic_pointer_cast<DataFlow>(element_) != nullptr) {
    std::dynamic_pointer_cast<DataFlow>(element_)->UpdateDataItem(data_item);
  }
  if (std::dynamic_pointer_cast<DataStorage>(element_) != nullptr) {
    std::dynamic_pointer_cast<DataStorage>(element_)->UpdateDataItem(data_item);
  }

  ImGui::PopID();
  ImGui::Separator();
}

void DataItemPopup::SetData(
    std::shared_ptr<Element> element, std::uint64_t data_item) {
  element_ = std::move(element);
  data_item_id_ = data_item;
}
