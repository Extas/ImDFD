
#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATASTORAGENODE_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATASTORAGENODE_H_

#include "element/Node.h"

#include "data/DataStorage.h"
#include <utility>

class DataStorageNode : public Node {
public:
  DataStorageNode(const std::string &name, std::pair<float, float> position,
      DataStorage dataStorage)
      : Node(name, position), m_dataStorage(std::move(dataStorage)) {
  }

  [[nodiscard]] auto GetDataStorage() const -> const DataStorage & {
    return m_dataStorage;
  }

  // Add more methods specific to DataStorageNode here

private:
  DataStorage m_dataStorage;
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATASTORAGENODE_H_
