#include "imgui.h"
#include <dfd_editor/DataItemPopup.h>
#include <dfd_model/DataFlow.h>
#include <signal/SignalHandel.h>
#include <string>
#include <ui/Widgets.h>
#include <vector>

DataItemPopup::DataItemPopup() : BasePopup("Data Items") {
}

void DataItemPopup::DrawContents() {
  DrawDataItems();

  DrawAddDataItemButton();
  ImGui::SameLine();
  DarwAddDataItemPopup();

  if (ImGui::Button("Close")) {
    ImGui::CloseCurrentPopup();
  }
}
void DataItemPopup::DarwAddDataItemPopup() {
  auto all_data_items = DataItem::GetAllItems();

  std::map<uint64_t, std::string> data_items_map;
  for (const auto &data_item : all_data_items) {
    data_items_map[data_item->GetElementId()] =
        data_item->GetName().value().get();
  }

  imdfd::ui::widgets::ListWithFilterPopup popup(
      "My List", data_items_map, [this, &all_data_items](uint64_t item_id) {
        for (const auto &data_item : all_data_items) {
          if (data_item->GetElementId() == item_id) {
            data_items_->push_back(data_item);
            break;
          }
        }
      });

  if (ImGui::Button("Add Existing Data Item")) {
    popup.Open();
  }

  popup.Draw();
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

  bool should_remove_data_item = false;

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

  if (ImGui::Button("Delete Data Item")) {
    should_remove_data_item = true;
  }

  if (should_remove_data_item) {
    if (std::dynamic_pointer_cast<DataFlow>(element_) != nullptr) {
      std::dynamic_pointer_cast<DataFlow>(element_)->RemoveDataItem(data_item);
    }
    if (std::dynamic_pointer_cast<DataStorage>(element_) != nullptr) {
      std::dynamic_pointer_cast<DataStorage>(element_)->RemoveDataItem(
          data_item);
    }
  }

  ImGui::PopID();
  ImGui::Separator();
}

void DataItemPopup::LoadDataItems(
    std::vector<std::shared_ptr<DataItem>> &data_items) {
  data_items_ = &data_items;
}

void DataItemPopup::DrawAddDataItemButton() {
  if (ImGui::Button("Create New Data Item")) {
    if (data_items_ != nullptr) {
      if (std::dynamic_pointer_cast<DataFlow>(element_) != nullptr) {
        std::dynamic_pointer_cast<DataFlow>(element_)->AddDataItem(
            DataItem::CreateDataItem("New Data Item", "No Type"));
      }
      if (std::dynamic_pointer_cast<DataStorage>(element_) != nullptr) {
        std::dynamic_pointer_cast<DataStorage>(element_)->AddDataItem(
            DataItem::CreateDataItem("New Data Item", "No Type"));
      }
    }
  }
}

void DataItemPopup::SetDataFlow(std::shared_ptr<Element> data_flow) {
  element_ = data_flow;
  if (std::dynamic_pointer_cast<DataFlow>(data_flow) != nullptr) {
    LoadDataItems(std::dynamic_pointer_cast<DataFlow>(data_flow)->data_items_);
  }
  if (std::dynamic_pointer_cast<DataStorage>(data_flow) != nullptr) {
    LoadDataItems(
        std::dynamic_pointer_cast<DataStorage>(data_flow)->stored_data_items_);
  }
}
