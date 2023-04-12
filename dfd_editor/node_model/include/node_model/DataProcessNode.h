#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATAPROCESSNODE_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATAPROCESSNODE_H_

#include "data/DataProcessData.h"
#include "element/Node.h"
#include "signal/SignalHandel.h"

#include <functional>
#include <utility>

class DataProcessNode : public Node {
public:
  DataProcessNode(uint64_t node_id, std::string *name,
      std::pair<float, float> *position, std::string *description,
      int64_t node_editor_id)
      : Node(node_id, name, position),
        data_processing_(description, node_editor_id) {
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
  void SetProcessName(std::string *new_process_name);
  void SetProcessingContent(const std::string &new_processing_content);
  void NavigateToInputDataFlow(int64_t index);
  void NavigateToOutputDataFlow(int64_t index);

  // Add more methods specific to DataProcessNode here

private:
  DataProcessData data_processing_;

public:
  [[nodiscard]] auto GetDataProcessing() const -> const DataProcessData &;

  [[nodiscard]] auto GetDataProcessing() -> DataProcessData &;
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATAPROCESSNODE_H_
