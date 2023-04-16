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
  uint64_t id = json["id"].get<uint64_t>();
  std::string name = json["name"].get<std::string>();
  std::pair<float, float> pos = json["pos"].get<std::pair<float, float>>();

  auto data_storage = Create(id, std::move(name), pos);

  for (const auto &data_item_json : json["stored_data_items"]) {
    auto data_item = DataItem::Deserialize(data_item_json);
    data_storage->AddDataItem(data_item);
  }

  return data_storage;
}
void DataStorage::AddDataItem(std::shared_ptr<DataItem> data_item) {
  if (std::find(data_items_.begin(), data_items_.end(), data_item) !=
      data_items_.end()) {
    return;
  }
  data_items_.push_back(data_item);
}

auto DataStorage::Serialize() const -> nlohmann::json {
  nlohmann::json json = DfdNode::Serialize("DataStorage");

  nlohmann::json stored_data_items_json = nlohmann::json::array();
  for (const auto &data_item : data_items_) {
    stored_data_items_json.push_back(data_item->Serialize());
  }
  json["stored_data_items"] = stored_data_items_json;

  return json;
}
void DataStorage::RemoveDataItem(const std::shared_ptr<DataItem> &data_item) {
  data_items_.erase(
      std::remove(data_items_.begin(), data_items_.end(), data_item),
      data_items_.end());
}
auto DataStorage::GetDataItems() const
    -> std::vector<std::shared_ptr<DataItem>> {
  return data_items_;
}
