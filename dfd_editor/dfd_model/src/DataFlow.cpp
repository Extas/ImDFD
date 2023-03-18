#include <dfd_model/DataFlow.h>

#include <utility>

DataFlow::DataFlow(std::string name, const std::shared_ptr<DfdNode> &source,
    const std::shared_ptr<DfdNode> &destination, std::pair<float, float> pos)
    : Element(pos), name_(std::move(name)), source_(source),
      destination_(destination) {
}
auto DataFlow::Serialize() const -> std::string {
  return {};
}
auto DataFlow::IsValid() const -> bool {
  return true;
}
