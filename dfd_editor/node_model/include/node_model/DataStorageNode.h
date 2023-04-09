
#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATASTORAGENODE_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATASTORAGENODE_H_

#include "element/Node.h"

#include <utility>

class DataStorageNode : public Node {
public:
  DataStorageNode(
      uint64_t node_id, std::string *name, std::pair<float, float> *position)
      : Node(node_id, name, position) {
  }
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATASTORAGENODE_H_
