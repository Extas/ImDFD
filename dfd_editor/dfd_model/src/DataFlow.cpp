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
      std::move(name), std::move(source), std::move(destination), pos));
  return data_flow;
}
auto DataFlow::Create(std::string name, std::shared_ptr<DfdNode> source,
    std::shared_ptr<DfdNode> destination, std::pair<float, float> pos)
    -> std::shared_ptr<DataFlow> {
  auto data_flow = std::shared_ptr<DataFlow>(new DataFlow(
      std::move(name), std::move(source), std::move(destination), pos));
//  data_flow->Connect();
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
