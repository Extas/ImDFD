#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATAPROCESSNODE_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATAPROCESSNODE_H_

#include "data/DataProcess.h"
#include "element/Node.h"

#include <functional>
#include <utility>

class DataProcessNode : public Node {
public:
  DataProcessNode(const std::string &name, std::pair<float, float> position,
      DataProcess dataProcessing)
      : Node(name, position), data_processing_(std::move(dataProcessing)) {
  }

  void DrawCustomContent() const override;

  void SetProcessName(const std::string &new_process_name);
  void SetProcessingContent(const std::string &new_processing_content);
  void NavigateToSubDataFlowDiagram();
  void NavigateToInputDataFlow(size_t index);
  void NavigateToOutputDataFlow(size_t index);

  // Add more methods specific to DataProcessNode here

private:
  DataProcess data_processing_;

  std::function<void()> open_dfd_callback_;

public:
  [[nodiscard]] auto GetDataProcessing() const -> const DataProcess & {
    return data_processing_;
  }

  [[nodiscard]] auto GetDataProcessing() -> DataProcess & {
    return data_processing_;
  }

  void SetOpenDFDCallback(std::function<void()> open_dfd_callback);
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATAPROCESSNODE_H_
