#include <dfd_model/ExternalEntity.h>

#include <utility>
ExternalEntity::ExternalEntity(std::string name, std::pair<float, float> pos)
    : DfdNode(std::move(name), pos) {
}
