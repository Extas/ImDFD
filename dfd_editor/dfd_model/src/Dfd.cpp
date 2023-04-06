#include <dfd_model/Dfd.h>

#include <logging/Logger.h>
#include <nlohmann/json.hpp>
#include <utility>

Dfd::Dfd(std::string name) : name_(std::move(name)) {
}

Dfd::Dfd(uint64_t id, std::string name) : Element(id), name_(std::move(name)) {
}

void Dfd::CreateTestData() {
  auto external_entity =
      CreateExternalEntityNode("ExternalEntity", std::make_pair(0, 0));
  auto data_storage =
      CreateDataStorageNode("DataStorage", std::make_pair(1000, 0));
  auto data_process =
      CreateDataProcessNode("DataProcess", std::make_pair(500, 0));

  auto data_item = DataItem::CreateStringDataItem("DataItem1", "string");
  data_storage->stored_data_items_.push_back(data_item);
  data_items_.push_back(data_item);

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

auto Dfd::CreateDataProcessNode(const std::string &name,
    const std::pair<float, float> &pos) -> std::shared_ptr<DataProcess> {
  auto data_process = DataProcess::Create(name, pos);
  data_processes_.push_back(data_process);

  Logger::Trace("[DFD {}]: Create DataProcess Node ({}, pos({},{}))",
      GetElementId(), data_process->name_, data_process->position_.first,
      data_process->position_.second);
  return data_process;
}

auto Dfd::CreateDataStorageNode(const std::string &name,
    const std::pair<float, float> &pos) -> std::shared_ptr<DataStorage> {
  auto data_storage = DataStorage::Create(name, pos);
  data_storages_.push_back(data_storage);
  return data_storage;
}

auto Dfd::CreateExternalEntityNode(const std::string &name,
    const std::pair<float, float> &pos) -> std::shared_ptr<ExternalEntity> {
  auto external_entity = ExternalEntity::Create(name, pos);
  external_entities_.push_back(external_entity);
  return external_entity;
}
auto Dfd::AddNode(const std::string &node_type,
    const std::pair<float, float> &pos, const std::string &name) -> uint64_t {
  auto new_node_name = name;
  if (new_node_name.empty()) {
    new_node_name = node_type;
  }

  std::shared_ptr<Element> new_node;
  if (node_type == "DataProcess") {
    new_node = CreateDataProcessNode(new_node_name, pos);
  } else if (node_type == "DataStorage") {
    new_node = CreateDataStorageNode(new_node_name, pos);
  } else if (node_type == "ExternalEntity") {
    new_node = CreateExternalEntityNode(new_node_name, pos);
  }
  return new_node->GetElementId();
}
