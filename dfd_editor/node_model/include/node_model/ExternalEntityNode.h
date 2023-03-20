
#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_EXTERNALENTITYNODE_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_EXTERNALENTITYNODE_H_

#include "element/Node.h"

#include "data/ExternalEntity.h"
#include <utility>

class ExternalEntityNode : public Node {
public:
  ExternalEntityNode(std::string *name, std::pair<float, float> *position)
      : Node(name, position) {
  }

  [[nodiscard]] auto GetExternalEntity() const -> const ExternalEntity & {
    return external_entity_;
  }

  // Add more methods specific to ExternalEntityNode here

private:
  ExternalEntity external_entity_;
};
#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_EXTERNALENTITYNODE_H_
