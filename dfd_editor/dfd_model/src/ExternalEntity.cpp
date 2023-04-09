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
auto ExternalEntity::DeSerialize(nlohmann::json json)
    -> std::shared_ptr<ExternalEntity> {
  auto id = json["id"].get<uint64_t>();
  auto name = json["name"].get<std::string>();
  auto pos = json["pos"].get<std::pair<float, float>>();
  return Create(id, name, pos);
}
