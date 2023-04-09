#include <dfd_model/DataStorage.h>

DataStorage::DataStorage(std::string name, std::pair<float, float> pos)
    : DfdNode(std::move(name), pos) {
}

DataStorage::DataStorage(
    uint64_t id, std::string name, std::pair<float, float> pos)
    : DfdNode(id, std::move(name), pos) {
}
auto DataStorage::Create(std::string name, std::pair<float, float> pos)
    -> std::shared_ptr<DataStorage> {
  return std::shared_ptr<DataStorage>(new DataStorage(name, pos));
}
auto DataStorage::Create(uint64_t id, std::string name,
    std::pair<float, float> pos) -> std::shared_ptr<DataStorage> {
  return std::shared_ptr<DataStorage>(new DataStorage(id, name, pos));
}
auto DataStorage::DeSerialize(nlohmann::json json)
    -> std::shared_ptr<DataStorage> {
  auto id = json["id"].get<uint64_t>();
  auto name = json["name"].get<std::string>();
  auto pos = json["pos"].get<std::pair<float, float>>();

  return Create(id, name, pos);
}
void DataStorage::AddDataItem(std::shared_ptr<DataItem> data_item) {
  stored_data_items_.push_back(data_item);
}
