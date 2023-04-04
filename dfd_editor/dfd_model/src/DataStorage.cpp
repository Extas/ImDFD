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
