#include <dfd_model/Dfd.h>

#include <logging/Logger.h>
#include <nlohmann/json.hpp>
#include <utility>

Dfd::Dfd(std::string name) : name_(std::move(name)) {
}

Dfd::Dfd(uint64_t id, std::string name) : Element(id), name_(std::move(name)) {
}

void Dfd::CreateExampleData() {
  auto external_entity =
      CreateExternalEntityNode("ExternalEntity", std::make_pair(0, 0));
  auto data_storage =
      CreateDataStorageNode("DataStorage", std::make_pair(1000, 0));
  auto data_process =
      CreateDataProcessNode("DataProcess", std::make_pair(500, 0));

  auto string_data_item = DataItem::CreateDataItem("DataItem1", "string");
  string_data_item->AddDataDef("format", "string", "nnnn-nnnn-nnnn-nnnn");
  auto integer_data_item = DataItem::CreateDataItem("DataItem2", "integer");
  integer_data_item->AddDataDef("min", "integer", "0");
  integer_data_item->AddDataDef("max", "integer", "3");
  integer_data_item->AddSubDataItem(string_data_item);
  integer_data_item->AddSubDataItem(string_data_item);
  integer_data_item->AddSubDataItem(string_data_item);
  data_storage->AddDataItem(string_data_item);
  data_storage->AddDataItem(integer_data_item);
  data_items_.push_back(string_data_item);

  auto data_flow_1 = CreateDataFlow(
      "DataFlow1", external_entity, data_process, std::make_pair(0, 0));
  data_flow_1->AddDataItem(string_data_item);
  data_flows_.push_back(data_flow_1);

  auto data_flow_2 = CreateDataFlow(
      "DataFlow2", data_process, data_storage, std::make_pair(0, 0));
  data_flow_2->AddDataItem(integer_data_item);
  data_flows_.push_back(data_flow_2);
}

[[nodiscard]] auto Dfd::GetJsonString() const -> std::string {
  return Serialize().dump(4);
}

[[nodiscard]] auto Dfd::Serialize() const -> nlohmann::json {
  nlohmann::json json_obj;

  json_obj["id"] = GetElementId();
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
      GetElementId(), data_process->GetName().get(),
      data_process->GetPosition().get().first,
      data_process->GetPosition().get().second);
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
auto Dfd::GetName() const -> std::string {
  return name_;
}
auto Dfd::CreateDataFlow(const std::string &name,
    const std::shared_ptr<DfdNode> &src, const std::shared_ptr<DfdNode> &dst,
    const std::pair<float, float> &pos) -> std::shared_ptr<DataFlow> {
  auto data_flow = DataFlow::Create(name, src, dst, pos);
  data_flows_.push_back(data_flow);
  return data_flow;
}
auto Dfd::GetNodeById(uint64_t node_id) -> std::shared_ptr<DfdNode> {
  auto iter = std::find_if(data_processes_.begin(), data_processes_.end(),
      [node_id](const auto &node) { return node->GetElementId() == node_id; });
  if (iter != data_processes_.end()) {
    return *iter;
  }

  auto iter2 = std::find_if(data_storages_.begin(), data_storages_.end(),
      [node_id](const auto &node) { return node->GetElementId() == node_id; });
  if (iter2 != data_storages_.end()) {
    return *iter2;
  }

  auto iter3 = std::find_if(external_entities_.begin(),
      external_entities_.end(),
      [node_id](const auto &node) { return node->GetElementId() == node_id; });
  if (iter3 != external_entities_.end()) {
    return *iter3;
  }

  return nullptr;
}
auto Dfd::DeleteFlow(uint64_t flow_id) -> bool {
  auto iter = std::find_if(data_flows_.begin(), data_flows_.end(),
      [flow_id](const auto &flow) { return flow->GetElementId() == flow_id; });
  if (iter != data_flows_.end()) {
    data_flows_.erase(iter);
    return true;
  }
  return false;
}
auto Dfd::AddDataFlow(const std::string &name, uint64_t src_node_id,
    uint64_t dst_node_id) -> uint64_t {
  auto src = GetNodeById(src_node_id);
  auto dst = GetNodeById(dst_node_id);
  if (src && dst) {
    auto data_flow = CreateDataFlow(name, src, dst, {0, 0});
    return data_flow->GetElementId();
  }
  return 0;
}
auto Dfd::DeleteNode(uint64_t node_id) -> bool {
  DfdNode *to_delete = nullptr;
  auto iter = std::find_if(data_processes_.begin(), data_processes_.end(),
      [node_id](const auto &node) { return node->GetElementId() == node_id; });
  if (iter != data_processes_.end()) {
    auto data_process = *iter;
    data_processes_.erase(iter);
    to_delete = data_process.get();
  }

  auto iter2 = std::find_if(data_storages_.begin(), data_storages_.end(),
      [node_id](const auto &node) { return node->GetElementId() == node_id; });
  if (iter2 != data_storages_.end()) {
    auto data_storage = *iter2;
    data_storages_.erase(iter2);
    to_delete = data_storage.get();
  }

  auto iter3 = std::find_if(external_entities_.begin(),
      external_entities_.end(),
      [node_id](const auto &node) { return node->GetElementId() == node_id; });

  if (iter3 != external_entities_.end()) {
    auto external_entity = *iter3;
    external_entities_.erase(iter3);
    to_delete = external_entity.get();
  }

  if (to_delete == nullptr) {
    return false;
  }

  // delete all flows connected to this node,use flow.HasNode(node_id) to check
  data_flows_.erase(
      std::remove_if(data_flows_.begin(), data_flows_.end(),
          [node_id](const auto &flow) { return flow->HasNode(node_id); }),
      data_flows_.end());

  return true;
}
auto Dfd::GetFlowById(uint64_t flow_id) -> std::shared_ptr<DataFlow> {
  auto iter = std::find_if(data_flows_.begin(), data_flows_.end(),
      [flow_id](const auto &flow) { return flow->GetElementId() == flow_id; });
  if (iter != data_flows_.end()) {
    return *iter;
  }
  return nullptr;
}

[[nodiscard]] auto Dfd::DeSerialize(nlohmann::json json)
    -> std::shared_ptr<Dfd> {
  auto id = json["id"].get<uint64_t>();
  auto name = json["name"].get<std::string>();

  auto dfd = std::make_shared<Dfd>(id, name);

  // Deserialize DataProcess nodes
  for (const auto &process_json : json["data_processes"]) {
    auto process_node = DataProcess::DeSerialize(process_json);
    dfd->data_processes_.push_back(process_node);
  }

  for (const auto &storage_json : json["data_storages"]) {
    auto storage_node = DataStorage::DeSerialize(storage_json);
    dfd->data_storages_.push_back(storage_node);
  }

  for (const auto &entity_json : json["external_entities"]) {
    auto entity_node = ExternalEntity::DeSerialize(entity_json);
    dfd->external_entities_.push_back(entity_node);
  }

  for (const auto &item_json : json["data_items"]) {
    auto data_item = DataItem::Deserialize(item_json);
    dfd->data_items_.push_back(data_item);
  }

  for (const auto &flow_json : json["data_flows"]) {
    auto data_flow = DataFlow::DeSerialize(
        flow_json, [&](uint64_t nodeId) { return dfd->GetNodeById(nodeId); });
    dfd->data_flows_.push_back(data_flow);
  }

  return dfd;
}
auto Dfd::LoadFromJsonString(const std::string &json) -> std::shared_ptr<Dfd> {
  auto json_obj = nlohmann::json::parse(json);
  auto dfd = DeSerialize(json_obj);
  return dfd;
}
