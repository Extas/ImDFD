
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

  void DrawCustomContent() const override{};
  void DrawCustomStyleStart() const override {
    ed::PushStyleColor(ed::StyleColor_NodeBorder, ImColor(50, 200, 50, 255));
    ed::PushStyleVar(ed::StyleVar_NodeRounding, 0.0F);
  }
  void DrawCustomStyleEnd() const override {
    ed::PopStyleColor();
    ed::PopStyleVar();
  }
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATASTORAGENODE_H_
