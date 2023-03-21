#include <dfd_model/DataFlow.h>

#include <utility>

DataFlow::DataFlow(std::string name, std::shared_ptr<DfdNode> source,
    std::shared_ptr<DfdNode> destination, std::pair<float, float> pos)
    : DfdNode(std::move(name), pos), source_(std::move(source)),
      destination_(std::move(destination)) {
}

void DataFlow::Connect() {
  source_->output_data_flows_.push_back(shared_from_this());
  destination_->input_data_flows_.push_back(shared_from_this());
}

auto DataFlow::Serialize() const -> std::string {
  return {};
}
auto DataFlow::IsValid() const -> bool {
  return true;
}
