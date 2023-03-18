#include <dfd_model/ExternalEntity.h>

#include <utility>
ExternalEntity::ExternalEntity(std::string name) : DfdElement(std::move(name)) {
}
