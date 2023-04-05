#include <dfd_model/Dfd.h>

#include <nlohmann/json.hpp>
#include <utility>

Dfd::Dfd(std::string name) : name_(std::move(name)) {
}

Dfd::Dfd(uint64_t id, std::string name) : Element(id), name_(std::move(name)) {
}

void Dfd::CreateTestData() {
  auto external_entity =
      ExternalEntity::Create("ExternalEntity", std::make_pair(0, 0));
  external_entities_.push_back(external_entity);

  auto data_storage =
      DataStorage::Create("DataStorage", std::make_pair(1000, 0));
  data_storages_.push_back(data_storage);

  auto data_item = DataItem::CreateStringDataItem("DataItem1", "string");
  data_storage->stored_data_items_.push_back(data_item);
  data_items_.push_back(data_item);

  auto data_process =
      DataProcess::Create("DataProcess", std::make_pair(500, 0));
  data_processes_.push_back(data_process);

  auto data_flow_1 = DataFlow::Create(
      "DataFlow1", external_entity, data_process, std::make_pair(100, 0));
  data_flow_1->Connect();
  data_flows_.push_back(data_flow_1);

  auto data_flow_2 = DataFlow::Create(
      "DataFlow2", data_process, data_storage, std::make_pair(600, 0));
  data_flow_2->Connect();
  data_flows_.push_back(data_flow_2);
}

[[nodiscard]] auto Dfd::GetJsonString() const -> std::string {
  return Serialize().dump(4);
}
[[nodiscard]] auto Dfd::Serialize() const -> nlohmann::json {
  nlohmann::json json_obj;

  json_obj["name"] = name_;

  auto serialize_elements = [](const auto &elements, const std::string &key) {
    nlohmann::json arr = nlohmann::json::array();
    for (const auto &element : elements) {
      arr.push_back(element->Serialize());
    }
    return arr;
  };

  json_obj["data_flows"] = serialize_elements(data_flows_, "data_flows");
  json_obj["data_items"] = serialize_elements(data_items_, "data_items");
  json_obj["data_processes"] =
      serialize_elements(data_processes_, "data_processes");
  json_obj["external_entities"] =
      serialize_elements(external_entities_, "external_entities");
  json_obj["data_storages"] =
      serialize_elements(data_storages_, "data_storages");

  return json_obj;
}

auto Dfd::IsValid() const -> bool {
  return false;
}
