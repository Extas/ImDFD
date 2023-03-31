#include <dfd_model/DataFlow.h>

void DataFlow::Connect() {
  source_->output_data_flows_.push_back(shared_from_this());
  destination_->input_data_flows_.push_back(shared_from_this());
}
auto DataFlow::Serialize() const -> std::string {
  // Call the base class implementation
  std::string base_serialized = DfdNode::Serialize();
  nlohmann::json j = nlohmann::json::parse(base_serialized);

  // Serialize DataFlow-specific properties
  j["source_id"] = source_->GetElementId();
  j["destination_id"] = destination_->GetElementId();

  // Serialize data_items_
  nlohmann::json data_items_json = nlohmann::json::array();
  for (const auto &kItem : data_items_) {
    data_items_json.push_back(nlohmann::json::parse(kItem->Serialize()));
  }
  j["data_items"] = data_items_json;

  return j.dump();
}
