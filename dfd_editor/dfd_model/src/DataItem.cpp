#include "dfd_model/data_type/DataItemType.h"
#include <dfd_model/DataItem.h>
#include <nlohmann/json.hpp>

auto DataItem::Serialize() const -> nlohmann::json {
  nlohmann::json json;
  json["id"] = GetElementId();
  json["name"] = name_;
  json["data_type"] = data_type_->Serialize();
  return json;
}

auto DataItem::IsValid() const -> bool {
  return true;
}

auto DataItem::DeSerialize(nlohmann::json json) -> std::shared_ptr<DataItem> {
  auto id = json["id"].get<uint64_t>();
  auto name = json["name"].get<std::string>();
  auto data_type_json = json["data_type"];
  auto base_data_type = DataItemType::DeSerialize(data_type_json);

  std::shared_ptr<DataItemType> data_type;

  if (data_type_json["type"] == "string") {
    auto string_data_type =
        std::dynamic_pointer_cast<StringDataType>(base_data_type);
    data_type = string_data_type;
  } else if (data_type_json["type"] == "integer") {
    auto integer_data_type =
        std::dynamic_pointer_cast<IntegerDataType>(base_data_type);
    data_type = integer_data_type;
  } else {
    throw std::runtime_error("Unknown data type");
  }

  return std::shared_ptr<DataItem>(new DataItem(id, name, data_type));
}

auto DataItemType::DeSerialize(nlohmann::json json)
    -> std::shared_ptr<DataItemType> {
  if (json["type"] == "string") {
    return StringDataType::DeSerialize(json);
  }
  if (json["type"] == "integer") {
    return IntegerDataType::DeSerialize(json);
  }
  throw std::runtime_error("Unknown data type");
}
