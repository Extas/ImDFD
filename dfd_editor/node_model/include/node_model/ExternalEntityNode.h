
#ifndef IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODE_MODEL_EXTERNALENTITYNODE_H_
#define IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODE_MODEL_EXTERNALENTITYNODE_H_

#include "element/Node.h"

#include "data/ExternalEntity.h"
#include <utility>

class ExternalEntityNode : public Node {
public:
  ExternalEntityNode(const std::string &name, std::pair<float, float> position,
      ExternalEntity externalEntity)
      : Node(name, position), m_externalEntity(std::move(externalEntity)) {
  }

  [[nodiscard]] auto GetExternalEntity() const -> const ExternalEntity & {
    return m_externalEntity;
  }

  // Add more methods specific to ExternalEntityNode here

private:
  ExternalEntity m_externalEntity;
};
#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODE_MODEL_EXTERNALENTITYNODE_H_
