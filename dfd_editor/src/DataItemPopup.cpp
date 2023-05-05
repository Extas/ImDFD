#include "imgui.h"
#include <dfd_editor/DataItemPopup.h>
#include <dfd_model/DataFlow.h>
#include <functional>
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
  static std::map<std::string, std::pair<std::string, std::string>> updates;
  updates.clear();
  static std::vector<std::string> keys_to_remove;
  keys_to_remove.clear();

  auto column_names = std::vector<std::string>{"Definition", "Value"};

  static std::vector<std::vector<std::reference_wrapper<std::string>>> rowData;
  rowData.clear();

  for (auto &data_def : data_item->GetDataDefs()) {
    rowData.push_back(std::vector<std::reference_wrapper<std::string>>{
        std::ref(data_def.first), std::ref(data_def.second)});
  }

  // Prepare action callbacks
  std::map<std::string, std::function<void(int)>> action_callbacks;
  action_callbacks["Delete"] = [&](int rowIndex) {
    auto it = data_item->GetDataDefs().begin();
    std::advance(it, rowIndex);
    keys_to_remove.push_back(it->first);
  };

  // Draw the custom table
  imdfd::ui::widgets::DrawCustomTable(column_names, rowData, action_callbacks);

  // Apply updates
  for (const auto &key : keys_to_remove) {
    data_item->RemoveDataDef(key);
  }

  if (ImGui::Button("Create New Data Definition")) {
    data_item->CreateDataDef("Definition", "Value");
  }

  ImGui::Separator();
  ImGui::Text("Used By: ");
  ImGui::Indent();
  for (const auto &data_flow : data_item->GetDataFlows()) {
    if (ImGui::Button(data_flow->GetName().get().c_str())) {
      SignalHandel::Instance().navigate_element_onclick_(
          data_flow->GetElementId());
      ImGui::CloseCurrentPopup();
    }
  }
  ImGui::Unindent();
  ImGui::Separator();

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
