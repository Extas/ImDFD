#include <dfd_model/DataFlow.h>

#include <utility>

DataFlow::DataFlow(std::string name, const std::shared_ptr<DfdNode> &source,
    const std::shared_ptr<DfdNode> &destination, std::pair<float, float> pos)
    : DfdNode(std::move(name), pos), source_(source),
      destination_(destination) {
}
auto DataFlow::Serialize() const -> std::string {
  return {};
}
auto DataFlow::IsValid() const -> bool {
  return true;
}
