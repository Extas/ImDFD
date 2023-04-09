#include <dfd_model/DataItem.h>
#include <nlohmann/json.hpp>

auto DataItem::Serialize() const -> nlohmann::json {
  nlohmann::json json;
  json["id"] = GetElementId();
  json["name"] = name_;
  json["type"] = date_type_name_;

  for (const auto &[desc, value_pair] : data_map_) {
    json["data"][desc] = {
        {"type", value_pair.first}, {"value", value_pair.second}};
  }

  nlohmann::json sub_data_items_json = nlohmann::json::array();
  for (const auto &sub_data_item : sub_data_items_) {
    sub_data_items_json.push_back(sub_data_item->Serialize());
  }
  json["sub_data_items"] = sub_data_items_json;

  return json;
}

auto DataItem::IsValid() const -> bool {
  return true;
}

auto DataItem::DeSerialize(nlohmann::json json) -> std::shared_ptr<DataItem> {
  uint64_t id = json["id"].get<uint64_t>();
  std::string name = json["name"].get<std::string>();
  std::string type = json["type"].get<std::string>();

  if (type == "string") {
    return StringDataItem::DeSerialize(json);
  } else if (type == "integer") {
    return IntegerDataItem::DeSerialize(json);
  } else {
    throw std::runtime_error("Unknown data item type: " + type);
  }
}

auto DataItem::CreateStringDataItem(std::string name, std::string fmt)
    -> std::shared_ptr<DataItem> {
  auto string_data_item =
      std::make_shared<StringDataItem>(std::move(name), std::move(fmt));
  string_data_item->AddData();
  return string_data_item;
}
auto DataItem::CreateStringDataItemWithId(uint64_t id, std::string name,
    std::string fmt) -> std::shared_ptr<DataItem> {
  auto string_data_item =
      std::make_shared<StringDataItem>(id, std::move(name), std::move(fmt));
  string_data_item->AddData();
  return string_data_item;
}
auto DataItem::CreateIntegerDataItem(std::string name, int min_value,
    int max_value) -> std::shared_ptr<DataItem> {
  auto integer_data_item =
      std::make_shared<IntegerDataItem>(std::move(name), min_value, max_value);
  integer_data_item->AddData();
  return integer_data_item;
}
auto DataItem::CreateIntegerDataItemWithId(uint64_t id, std::string name,
    int min_value, int max_value) -> std::shared_ptr<DataItem> {
  auto integer_data_item = std::make_shared<IntegerDataItem>(
      id, std::move(name), min_value, max_value);
  integer_data_item->AddData();
  return integer_data_item;
}

auto StringDataItem::Serialize() const -> nlohmann::json {
  nlohmann::json json = DataItem::Serialize();
  json["fmt"] = fmt_;
  return json;
}
auto StringDataItem::DeSerialize(nlohmann::json json)
    -> std::shared_ptr<StringDataItem> {
  uint64_t id = json["id"].get<uint64_t>();
  std::string name = json["name"].get<std::string>();
  std::string fmt = json["fmt"].get<std::string>();

  auto item = std::make_shared<StringDataItem>(id, name, fmt);

  for (const auto &[desc, value_obj] : json["data"].items()) {
    item->data_map_[desc] = {value_obj["type"].get<std::string>(),
        value_obj["value"].get<std::string>()};
  }

  for (const auto &sub_data_item_json : json["sub_data_items"]) {
    item->sub_data_items_.push_back(DataItem::DeSerialize(sub_data_item_json));
  }

  return item;
}

auto IntegerDataItem::Serialize() const -> nlohmann::json {
  nlohmann::json json = DataItem::Serialize();
  json["min_value"] = min_value_;
  json["max_value"] = max_value_;
  return json;
}
auto IntegerDataItem::DeSerialize(nlohmann::json json)
    -> std::shared_ptr<IntegerDataItem> {
  uint64_t id = json["id"].get<uint64_t>();
  std::string name = json["name"].get<std::string>();
  int min_value = json["min_value"].get<int>();
  int max_value = json["max_value"].get<int>();

  auto item = std::make_shared<IntegerDataItem>(id, name, min_value, max_value);

  for (const auto &[desc, value_obj] : json["data"].items()) {
    item->data_map_[desc] = {value_obj["type"].get<std::string>(),
        value_obj["value"].get<std::string>()};
  }

  for (const auto &sub_data_item_json : json["sub_data_items"]) {
    item->sub_data_items_.push_back(DataItem::DeSerialize(sub_data_item_json));
  }

  return item;
}
