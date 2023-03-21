#include <dfd_model/Dfd.h>

#include <utility>

Dfd::Dfd(std::string name) : name_(std::move(name)) {
}

void Dfd::CreateTestData() {
  // 创建DataFlow, DataItem, DataProcessData, ExternalEntity和DataStorage实例
  // 并将它们添加到相应的容器中
  auto external_entity =
      std::make_shared<ExternalEntity>("ExternalEntity", std::make_pair(0, 0));
  external_entities_.push_back(external_entity);

  auto data_storage =
      std::make_shared<DataStorage>("DataStorage", std::make_pair(1000, 0));
  data_storages_.push_back(data_storage);

  auto data_item = std::make_shared<DataItem>("DataItem", StringDataType());
  data_storage->stored_data_items_.push_back(data_item);

  auto data_process =
      std::make_shared<DataProcess>("DataProcess", std::make_pair(400, 0));
  data_processes_.push_back(data_process);

  auto data_flow_1 = std::make_shared<DataFlow>(
      "DataFlow1", external_entity, data_process, std::make_pair(100, 0));
  data_flows_.push_back(data_flow_1);

  auto data_flow_2 = std::make_shared<DataFlow>(
      "DataFlow2", data_process, data_storage, std::make_pair(300, 0));
  data_flows_.push_back(data_flow_2);
}

auto Dfd::Serialize() const -> std::string {
  return {};
}
auto Dfd::IsValid() const -> bool {
  return false;
}
