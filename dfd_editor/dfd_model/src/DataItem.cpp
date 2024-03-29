#include <dfd_model/DataItem.h>

auto DataItem::IsValid() const -> bool {
  return true;
}

auto DataItem::Serialize() const -> nlohmann::json {
  nlohmann::json json;
  json["id"] = GetElementId();
  json["name"] = name_;
  json["type"] = data_type_name_;
  json["data_def"] = GetDataDefsJson();

  nlohmann::json sub_data_items_json = nlohmann::json::array();
  for (const auto &kSubDataItem : sub_data_items_) {
    sub_data_items_json.push_back(kSubDataItem->Serialize());
  }
  json["sub_data_items"] = sub_data_items_json;

  return json;
}

auto DataItem::Deserialize(nlohmann::json json) -> std::shared_ptr<DataItem> {
  uint64_t id = json.at("id");
  std::string name = json.at("name");
  std::string type_name = json.at("type");

  auto data_item =
      CreateDataItemWithId(id, std::move(name), std::move(type_name));

  auto data_defs_json = json.at("data_def");
  for (auto &data_def : data_defs_json.items()) {
    data_item->data_defs_.emplace_back(
        DataItem::DataDescription(data_def.key()),
        DataItem::DataValue(data_def.value()));
  }

  for (const auto &sub_data_item_json : json.at("sub_data_items")) {
    auto sub_data_item = Deserialize(sub_data_item_json);
    data_item->sub_data_items_.push_back(sub_data_item);
  }

  return data_item;
}

auto DataItem::CreateDataItem(std::string name, std::string type_name)
    -> std::shared_ptr<DataItem> {
  auto data_item =
      std::make_shared<DataItem>(std::move(name), std::move(type_name));
  all_items_.push_back(data_item);
  return data_item;
}
auto DataItem::CreateDataItemWithId(uint64_t id, std::string name,
    std::string type_name) -> std::shared_ptr<DataItem> {
  auto data_item =
      std::make_shared<DataItem>(id, std::move(name), std::move(type_name));
  all_items_.push_back(data_item);
  return data_item;
}
void DataItem::CreateDataDef(DataItem::DataDescription data_description,
    DataItem::DataValue data_value) {
  data_defs_.emplace_back(std::move(data_description), std::move(data_value));
}
