#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATAPROCESSNODE_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATAPROCESSNODE_H_

#include "data/DataProcessData.h"
#include "element/Node.h"
#include "signal/SignalHandel.h"

#include <functional>
#include <utility>

class DataProcessNode : public Node {
public:
  DataProcessNode(std::string *name, std::pair<float, float> *position,
      std::string *description, int node_editor_id)
      : Node(name, position), data_processing_(description, node_editor_id) {
  }

  void DrawCustomContent() const override;

  static void NavigateToNodeEditorById(int node_editor_id);
  void SetProcessName(const std::string &new_process_name);
  void SetProcessingContent(const std::string &new_processing_content);
  void NavigateToInputDataFlow(size_t index);
  void NavigateToOutputDataFlow(size_t index);

  // Add more methods specific to DataProcessNode here

private:
  DataProcessData data_processing_;

public:
  [[nodiscard]] auto GetDataProcessing() const -> const DataProcessData &;

  [[nodiscard]] auto GetDataProcessing() -> DataProcessData &;
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATAPROCESSNODE_H_
