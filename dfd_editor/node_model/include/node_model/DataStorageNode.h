
#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATASTORAGENODE_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATASTORAGENODE_H_

#include "element/Node.h"

#include "data/DataStorage.h"
#include <utility>

class DataStorageNode : public Node {
public:
  DataStorageNode(std::string *name, std::pair<float, float> *position)
      : Node(name, position) {
  }

  [[nodiscard]] auto GetDataStorage() const -> const DataStorage & {
    return data_storage_;
  }

  // Add more methods specific to DataStorageNode here

private:
  DataStorage data_storage_;
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATASTORAGENODE_H_
