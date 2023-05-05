#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATAPROCESSNODE_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATAPROCESSNODE_H_

#include "element/Node.h"
#include "signal/SignalHandel.h"

#include <functional>
#include <utility>

class DataProcessNode : public Node {
public:
  DataProcessNode(uint64_t node_id, std::reference_wrapper<std::string> name,
      std::reference_wrapper<std::pair<float, float>> position,
      std::reference_wrapper<std::string> description, int64_t node_editor_id)
      : Node(node_id, name, position), description_(description),
        sub_data_flow_diagram_id_(node_editor_id) {
  }

  void DrawCustomContent() const override;
  void DrawCustomStyleStart() const override {
    ed::PushStyleColor(ed::StyleColor_NodeBorder, ImColor(200, 50, 50, 255));
    ed::PushStyleVar(ed::StyleVar_NodeRounding, 50.0F);
  }
  void DrawCustomStyleEnd() const override {
    ed::PopStyleColor();
    ed::PopStyleVar();
  }

  static void NavigateToNodeEditorById(int64_t node_editor_id);

private:
  int64_t sub_data_flow_diagram_id_;
  std::reference_wrapper<std::string> description_;
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATAPROCESSNODE_H_
