#include <dfd_model/DataFlow.h>

#include <utility>

void DataFlow::Connect() {
  source_->output_data_flows_.push_back(shared_from_this());
  destination_->input_data_flows_.push_back(shared_from_this());
}
auto DataFlow::Serialize() const -> nlohmann::json {
  // Call the base class implementation
  nlohmann::json json = DfdNode::Serialize();

  // Serialize DataFlow-specific properties
  json["source_id"] = source_->GetElementId();
  json["destination_id"] = destination_->GetElementId();

  // Serialize data_items_
  nlohmann::json data_items_json = nlohmann::json::array();
  for (const auto &kItem : data_items_) {
    data_items_json.push_back(kItem->Serialize());
  }
  json["data_items"] = data_items_json;

  return json;
}

auto DataFlow::Create(uint64_t id, std::string name,
    std::shared_ptr<DfdNode> source, std::shared_ptr<DfdNode> destination,
    std::pair<float, float> pos) -> std::shared_ptr<DataFlow> {
  auto data_flow = std::shared_ptr<DataFlow>(new DataFlow(
      id, std::move(name), std::move(source), std::move(destination), pos));
  data_flow->Connect();
  return data_flow;
}
auto DataFlow::Create(std::string name, std::shared_ptr<DfdNode> source,
    std::shared_ptr<DfdNode> destination, std::pair<float, float> pos)
    -> std::shared_ptr<DataFlow> {
  auto data_flow = std::shared_ptr<DataFlow>(new DataFlow(
      std::move(name), std::move(source), std::move(destination), pos));
  data_flow->Connect();
  return data_flow;
}

DataFlow::DataFlow(std::string name, std::shared_ptr<DfdNode> source,
    std::shared_ptr<DfdNode> destination, std::pair<float, float> pos)
    : DfdNode(std::move(name), pos), source_(std::move(source)),
      destination_(std::move(destination)) {
}
DataFlow::DataFlow(uint64_t id, std::string name,
    std::shared_ptr<DfdNode> source, std::shared_ptr<DfdNode> destination,
    std::pair<float, float> pos)
    : DfdNode(id, std::move(name), pos), source_(std::move(source)),
      destination_(std::move(destination)) {
}

auto DataFlow::DeSerialize(nlohmann::json json,
    std::function<std::shared_ptr<DfdNode>(uint64_t)> find_node_by_id)
    -> std::shared_ptr<DataFlow> {
  auto id = json["id"].get<uint64_t>();
  auto name = json["name"].get<std::string>();
  auto pos = json["pos"].get<std::pair<float, float>>();
  auto source_id = json["source_id"].get<uint64_t>();
  auto destination_id = json["destination_id"].get<uint64_t>();

  auto source = find_node_by_id(source_id);
  auto destination = find_node_by_id(destination_id);

  auto data_flow = Create(id, name, source, destination, pos);

  // Deserialize data_items_
  auto data_items_json = json["data_items"].get<nlohmann::json>();
  for (const auto &kItem : data_items_json) {
    data_flow->data_items_.push_back(DataItem::Deserialize(kItem));
  }

  return data_flow;
}
auto DataFlow::HasNode(uint64_t node_id) const -> bool {
  return source_->GetElementId() == node_id ||
         destination_->GetElementId() == node_id;
}
void DataFlow::AddDataItem(std::shared_ptr<DataItem> data_item) {
  data_items_.push_back(std::move(data_item));
}
