#include <dfd_model/DataItem.h>
#include <nlohmann/json.hpp>

auto DataItem::Serialize() const -> std::string {
  nlohmann::json json;
  json["id"] = GetElementId();
  json["name"] = name_;
  json["data_type"] = data_type_->Serialize();
  return json.dump();
}
auto DataItem::IsValid() const -> bool {
  return true;
}
