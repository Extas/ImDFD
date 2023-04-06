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
