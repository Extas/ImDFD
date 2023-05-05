
#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_EXTERNALENTITYNODE_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_EXTERNALENTITYNODE_H_

#include "element/Node.h"

#include <utility>

class ExternalEntityNode : public Node {
public:
  ExternalEntityNode(uint64_t node_id, std::reference_wrapper<std::string> name,
      std::reference_wrapper<std::pair<float, float>> position)
      : Node(node_id, name, position) {
  }
  void DrawCustomContent() const override {};
  void DrawCustomStyleStart() const override {
    ed::PushStyleColor(ed::StyleColor_NodeBorder, ImColor(50, 50, 200, 255));
    ed::PushStyleVar(ed::StyleVar_NodeRounding, 0.0F);
  }
  void DrawCustomStyleEnd() const override {
    ed::PopStyleColor();
    ed::PopStyleVar();
  }
};
#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_EXTERNALENTITYNODE_H_
