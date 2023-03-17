#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATAPROCESSNODE_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATAPROCESSNODE_H_

#include "data/DataProcess.h"
#include "element/Node.h"

#include <functional>
#include <utility>

class DataProcessNode : public Node {
public:
  DataProcessNode(const std::string &name, std::pair<float, float> position,
      int node_editor_id)
      : Node(name, position), data_processing_(node_editor_id) {
  }

  void DrawCustomContent() const override;

  void SetProcessName(const std::string &new_process_name);
  void SetProcessingContent(const std::string &new_processing_content);
  void NavigateToNodeEditorById(int node_editor_id) const;
  void NavigateToInputDataFlow(size_t index);
  void NavigateToOutputDataFlow(size_t index);

  // Add more methods specific to DataProcessNode here

private:
  DataProcess data_processing_;

  std::function<void(int)> navigate_to_node_editor_callback_;

public:
  [[nodiscard]] auto GetDataProcessing() const -> const DataProcess &;

  [[nodiscard]] auto GetDataProcessing() -> DataProcess &;

  void SetNavigateToNodeEditorCallback(
      std::function<void(int)> navigate_to_node_editor_callback);
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATAPROCESSNODE_H_
