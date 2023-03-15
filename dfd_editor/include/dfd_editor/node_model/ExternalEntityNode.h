
#ifndef IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODE_MODEL_EXTERNALENTITYNODE_H_
#define IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODE_MODEL_EXTERNALENTITYNODE_H_

#include "Node.h"
#include "data/ExternalEntity.h"

class ExternalEntityNode : public Node {
public:
  ExternalEntityNode(const std::string &name, std::pair<float, float> position,
      const ExternalEntity &externalEntity)
      : Node(name, position), m_externalEntity(externalEntity) {
  }

  const ExternalEntity &GetExternalEntity() const {
    return m_externalEntity;
  }

  // Add more methods specific to ExternalEntityNode here

private:
  ExternalEntity m_externalEntity;
};
#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODE_MODEL_EXTERNALENTITYNODE_H_
