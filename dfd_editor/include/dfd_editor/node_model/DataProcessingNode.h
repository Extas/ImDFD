
#ifndef IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_DATAPROCESSINGNODE_H_
#define IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_DATAPROCESSINGNODE_H_

#include "Node.h"
#include "data/DataProcessing.h"

class DataProcessingNode : public Node {
public:
  DataProcessingNode(const std::string &name, std::pair<float, float> position,
      const DataProcessing &dataProcessing)
      : Node(name, position), m_dataProcessing(dataProcessing) {
  }

  const DataProcessing &GetDataProcessing() const {
    return m_dataProcessing;
  }

  // Add more methods specific to DataProcessingNode here

private:
  DataProcessing m_dataProcessing;
};

#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_DATAPROCESSINGNODE_H_
