#include <dfd_editor/DataItemPopup.h>
#include <dfd_model/DataFlow.h>
#include <imgui_stdlib.h>

void DataItemPopup::DrawContents() {
  // 绘制数据项相关的UI组件
  DrawDataItems();
  DrawAddDataItemButton();

  // 关闭子窗口的按钮
  if (ImGui::Button("Close")) {
    ImGui::CloseCurrentPopup();
  }
}

// 在DataItemPopup.cpp中实现
DataItemPopup::DataItemPopup() : BasePopup("Data Items") {
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
    ImGui::PushID(data_item->GetElementId());

    // 绘制数据项的名称
    ImGui::Text("Name: ");
    ImGui::SameLine();
    std::string name = data_item->GetName().value();
    ImGui::InputText("##Name", &name);

    // 绘制数据项的数据类型
    ImGui::Text("Data Type: ");
    ImGui::SameLine();
    std::string data_type_name = data_item->GetDateTypeName();
    ImGui::InputText("##DataType", &data_type_name);

    // 绘制子数据项列表
    ImGui::Text("Sub Data Items: ");
    ImGui::Indent();
    for (const auto &sub_data_item : data_item->GetSubDataItems()) {
      ImGui::BulletText("%s", sub_data_item->GetName().value().get().c_str());
    }
    ImGui::Unindent();

    // 绘制使用本数据项的数据流列表
    ImGui::Text("Used By Data Flows: ");
    ImGui::Indent();
    // 假设 data_item->GetDataFlows() 返回使用此数据项的数据流列表
    for (const auto &data_flow : data_item->GetDataFlows()) {
      ImGui::BulletText("%s", data_flow->GetName().value().get().c_str());
    }
    ImGui::Unindent();

    // 提供修改名称、修改类型等操作的UI组件
    if (ImGui::Button("Apply Changes")) {
      //      data_item->SetName(name);
      //      data_item->SetDataTypeName(data_type_name);
    }

    // 跳转到子数据项定义和使用本数据项的数据流定义的按钮
    if (ImGui::Button("View Sub Data Items")) {
      // 跳转到子数据项定义
      //      LoadDataItems(data_item->GetSubDataItems());
      Open();
    }

    ImGui::SameLine();
    if (ImGui::Button("View Data Flows")) {
      // 跳转到使用本数据项的数据流定义
      // 假设 LoadDataFlows 是一个加载数据流的方法
      //      LoadDataFlows(data_item->GetDataFlows());
      Open();
    }

    ImGui::PopID();
    ImGui::Separator();
  }
}

void DataItemPopup::LoadDataItems(
    std::vector<std::shared_ptr<DataItem>> &data_items) {
  data_items_ = &data_items;
}

void DataItemPopup::DrawAddDataItemButton() {
  if (ImGui::Button("Add Data Item")) {
    AddDataItem();
  }
}
void DataItemPopup::AddDataItem() {
  // 根据需要创建新的数据项并将其添加到data_items_中
}
