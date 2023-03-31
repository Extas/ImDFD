#include <dfd_model/ExternalEntity.h>

ExternalEntity::ExternalEntity(std::string name, std::pair<float, float> pos)
    : DfdNode(std::move(name), pos) {
}
ExternalEntity::ExternalEntity(
    uint64_t id, std::string name, std::pair<float, float> pos)
    : DfdNode(id, std::move(name), pos) {
}
