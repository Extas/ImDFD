
#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_EXTERNALENTITYNODE_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_EXTERNALENTITYNODE_H_

#include "element/Node.h"

#include "data/ExternalEntityData.h"
#include <utility>

class ExternalEntityNode : public Node {
public:
  ExternalEntityNode(
      uint64_t node_id, std::string *name, std::pair<float, float> *position)
      : Node(node_id, name, position) {
  }

  [[nodiscard]] auto GetExternalEntity() const -> const ExternalEntityData & {
    return external_entity_;
  }

  // Add more methods specific to ExternalEntityNode here

private:
  ExternalEntityData external_entity_;
};
#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_EXTERNALENTITYNODE_H_
