#define IMGUI_DEFINE_MATH_OPERATORS
#include <dfd_model/DataItem.h>
#include <logging/Logger.h>
#include <dfd_editor/InfoWindow.h>
#include <imgui.h>
#include <signal/SignalHandel.h>
#include <string>
#include <ui/Widgets.h>

InfoWindow::InfoWindow() : BaseWindow("Info") {
  SignalHandel::Instance().selected_node_.connect([this](int64_t node_id) {
    auto node = dfd_->GetNodeById(node_id);
    if (node) {
      Info new_info;
      info_ = new_info;
      info_.LoadElement(node);
    }
  });

  SignalHandel::Instance().selected_link_.connect([this](int64_t link_id) {
    auto link = dfd_->GetFlowById(link_id);
    if (link) {
      Info new_info;
      info_ = new_info;
      info_.LoadElement(link);
    }
  });
}

void InfoWindow::DrawContents() {
  info_.Update();
  auto name = info_.GetName();
  if (name.has_value()) {
    imdfd::ui::widgets::DrawTextNextLineEdit(name.value(), "Name:");
    ImGui::Separator();
  }
  auto description = info_.GetDescription();
  if (description.has_value()) {
    imdfd::ui::widgets::DrawTextNextLineEdit(
        description.value(), "Description:");
    ImGui::Separator();
  }

  auto &data_items = info_.GetDataItems();
  if (data_items.has_value()) {
    DrawDataItems(data_items.value());
    ImGui::Separator();
  }

  DrawFlows();
}
void InfoWindow::DrawFlows() {
  const auto &kInFlows = this->info_.GetInFlows();
  if (kInFlows.has_value() && !kInFlows.value().empty()) {
    ImGui::Text("In Flows");
    for (const auto &kFlows : kInFlows.value()) {
      if (ImGui::Button(kFlows.lock()->GetName().get().c_str())) {
        SignalHandel::Instance().navigate_element_onclick_(
            kFlows.lock()->GetElementId());
      }
    }
    ImGui::Separator();
  }
  const auto &kOutFlows = this->info_.GetOutFlows();
  if (kOutFlows.has_value() && !kOutFlows.value().empty()) {

    ImGui::Text("Out Flows");
    for (const auto &flows : kOutFlows.value()) {
      if (ImGui::Button(flows.lock()->GetName().get().c_str())) {
        SignalHandel::Instance().navigate_element_onclick_(
            flows.lock()->GetElementId());
      }
    }
    ImGui::Separator();
  }
}

void InfoWindow::DrawDataItems(std::vector<std::shared_ptr<DataItem>> &items) {
  ImGui::Text("Data Items:");

  using namespace imdfd::ui::widgets;
  auto column_names = std::vector<std::string>{"Name", "Type"};
  auto row_data =
      std::vector<std::vector<std::reference_wrapper<std::string>>>{};
  static std::map<int, std::shared_ptr<DataItem>> row_map;
  for (int i = 0; i < items.size(); i++) {
    row_data.push_back(std::vector<std::reference_wrapper<std::string>>{
        items[i]->GetName().value().get(),
        items[i]->GetDateTypeName().value().get()});
    row_map[i] = items[i];
  }
  static bool is_data_item_popup_open = false;
  auto action_callbacks = std::map<std::string, std::function<void(int)>>{
      {"Detail##",
          [this](int row) {
            Logger::Trace("action on row: {}", row);
            auto data_item_id = row_map[row]->GetElementId();
            data_item_popup_.SetData(info_.GetElement(), data_item_id);
            is_data_item_popup_open = true;
          }},
      {"Delete", [this](int row) {
         Logger::Trace("action on row: {}", row);
         auto data_item = info_.GetDataItems().value()[row];
         auto element = info_.GetElement();
         if (auto data_flow = std::dynamic_pointer_cast<DataFlow>(element)) {
           data_flow->RemoveDataItem(data_item);
         } else if (auto data_store =
                        std::dynamic_pointer_cast<DataStorage>(element)) {
           data_store->RemoveDataItem(data_item);
         }
       }}};
  if (is_data_item_popup_open) {
    data_item_popup_.Open();
    is_data_item_popup_open = false;
  }
  data_item_popup_.Draw();
  DrawCustomTable(column_names, row_data, action_callbacks);

  auto element = info_.GetElement();
  if (ImGui::Button("Create New Data Item")) {
    if (std::dynamic_pointer_cast<DataFlow>(element) != nullptr) {
      std::dynamic_pointer_cast<DataFlow>(element)->AddDataItem(
          DataItem::CreateDataItem("New Data Item", "No Type"));
    }
    if (std::dynamic_pointer_cast<DataStorage>(element) != nullptr) {
      Logger::Warn("Please create a new Data Item in Data Flow");
    }
  }

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
            auto element = info_.GetElement();
            if (std::dynamic_pointer_cast<DataFlow>(element) != nullptr) {
              std::dynamic_pointer_cast<DataFlow>(element)->AddDataItem(
                  data_item);
            }
            if (std::dynamic_pointer_cast<DataStorage>(element) != nullptr) {
              std::dynamic_pointer_cast<DataStorage>(element)->AddDataItem(
                  data_item);
            }
            break;
          }
        }
      });
  if (ImGui::Button("Add Existing Data Item")) {
    popup.Open();
  }
  popup.Draw();
}

void Info::LoadNode(const std::shared_ptr<DfdNode> &node) {
  if (node) {
    name_ = node->GetName();
    if (auto data_process = std::dynamic_pointer_cast<DataProcess>(node)) {
      description_ = node->GetDescription();
    } else if (auto data_store = std::dynamic_pointer_cast<DataStorage>(node)) {
      data_items_ = data_store->GetDataItems();
    } else if (auto data_flow = std::dynamic_pointer_cast<DataFlow>(node)) {
    }
    inflows_ = node->GetInputDataFlows();
    outflows_ = node->GetOutputDataFlows();
  }
}
void Info::LoadLink(const std::shared_ptr<DataFlow> &link) {
  if (link) {
    name_ = link->GetName();
    data_items_ = std::ref(link->data_items_);
  }
}
void Info::LoadElement(const std::shared_ptr<Element> &element) {
  current_element_ = element;
  if (current_element_) {
    if (auto link = std::dynamic_pointer_cast<DataFlow>(current_element_)) {
      LoadLink(link);
    } else if (auto node =
                   std::dynamic_pointer_cast<DfdNode>(current_element_)) {
      LoadNode(node);
    }
  }
}

auto Info::GetName() -> std::optional<std::reference_wrapper<std::string>> {
  return name_;
}
auto Info::GetDescription()
    -> std::optional<std::reference_wrapper<std::string>> {
  return description_;
}
auto Info::GetDataItems()
    -> std::optional<std::vector<std::shared_ptr<DataItem>>> & {
  return data_items_;
}
auto Info::GetElement() -> std::shared_ptr<Element> {
  return current_element_;
}
auto Info::GetInFlows() -> std::optional<std::vector<std::weak_ptr<DataFlow>>> {
  return inflows_;
}
auto Info::GetOutFlows()
    -> std::optional<std::vector<std::weak_ptr<DataFlow>>> {
  return outflows_;
}
void Info::Update() {
  LoadElement(current_element_);
}
void InfoWindow::LoadDfd(const std::shared_ptr<Dfd> &dfd) {
  dfd_ = dfd;
}
