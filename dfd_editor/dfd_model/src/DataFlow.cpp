#include <dfd_model/DataFlow.h>

#include <utility>

DataFlow::DataFlow(std::string name, const std::shared_ptr<DfdElement> &source,
    const std::shared_ptr<DfdElement> &destination)
    : name_(std::move(name)), source_(source), destination_(destination) {
}
auto DataFlow::serialize() const -> std::string {
  return {};
}
auto DataFlow::is_valid() const -> bool {
  return true;
}
