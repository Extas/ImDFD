#include <dfd_model/Dfd.h>
void Dfd::CreateTestData() {
  // 创建DataFlow, DataItem, DataProcessData, ExternalEntity和DataStorage实例
  // 并将它们添加到相应的容器中
  auto external_entity = std::make_shared<ExternalEntity>("ExternalEntity");
  external_entities_.push_back(external_entity);

  auto data_storage = std::make_shared<DataStorage>("DataStorage");
  data_storages_.push_back(data_storage);

  auto data_item = std::make_shared<DataItem>("DataItem", StringDataType());
  data_storage->stored_data_items_.push_back(data_item);

  auto data_process = std::make_shared<DataProcess>("DataProcess");
  data_processes_.push_back(data_process);

  auto data_flow1 =
      std::make_shared<DataFlow>("DataFlow1", external_entity, data_process);
  data_flows_.push_back(data_flow1);

  auto data_flow2 =
      std::make_shared<DataFlow>("DataFlow2", data_process, data_storage);
  data_flows_.push_back(data_flow2);
}
auto Dfd::serialize() const -> std::string {
  return {};
}
auto Dfd::is_valid() const -> bool {
  return false;
}
