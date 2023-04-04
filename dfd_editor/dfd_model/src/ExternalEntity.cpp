#include <dfd_model/ExternalEntity.h>

ExternalEntity::ExternalEntity(std::string name, std::pair<float, float> pos)
    : DfdNode(std::move(name), pos) {
}
ExternalEntity::ExternalEntity(
    uint64_t id, std::string name, std::pair<float, float> pos)
    : DfdNode(id, std::move(name), pos) {
}
auto ExternalEntity::Create(std::string name, std::pair<float, float> pos)
    -> std::shared_ptr<ExternalEntity> {
  return std::shared_ptr<ExternalEntity>(new ExternalEntity(name, pos));
}
auto ExternalEntity::Create(uint64_t id, std::string name,
    std::pair<float, float> pos) -> std::shared_ptr<ExternalEntity> {
  return std::shared_ptr<ExternalEntity>(new ExternalEntity(id, name, pos));
}
