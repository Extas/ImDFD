
#ifndef IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODE_MODEL_DATASTORAGENode_H_
#define IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODE_MODEL_DATASTORAGENode_H_

#include "Node.h"
#include "data/DataStorage.h"

class DataStorageNode : public Node {
public:
  DataStorageNode(const std::string &name, std::pair<float, float> position,
      const DataStorage &dataStorage)
      : Node(name, position), m_dataStorage(dataStorage) {
  }

  const DataStorage &GetDataStorage() const {
    return m_dataStorage;
  }

  // Add more methods specific to DataStorageNode here

private:
  DataStorage m_dataStorage;
};

#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODE_MODEL_DATASTORAGENode_H_
