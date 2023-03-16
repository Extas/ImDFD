
#ifndef IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_DATAPROCESSINGNODE_H_
#define IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_DATAPROCESSINGNODE_H_

#include "Node.h"

#include "data/DataProcessing.h"
#include <utility>

class DataProcessingNode : public Node {
public:
  DataProcessingNode(const std::string &name, std::pair<float, float> position,
      DataProcessing dataProcessing)
      : Node(name, position), m_dataProcessing(std::move(dataProcessing)) {
  }

  [[nodiscard]] auto GetDataProcessing() const -> const DataProcessing & {
    return m_dataProcessing;
  }

  // Add more methods specific to DataProcessingNode here

private:
  DataProcessing m_dataProcessing;
};

#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_DATAPROCESSINGNODE_H_
