
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAFLOW_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAFLOW_H_

#include "DataItem.h"
#include "DfdNode.h"

#include <memory>
#include <vector>

class DfdNode;

class DataFlow : public DfdNode, public std::enable_shared_from_this<DataFlow> {
public:
  DataFlow(std::string name, std::shared_ptr<DfdNode> source,
      std::shared_ptr<DfdNode> destination, std::pair<float, float> pos)
      : DfdNode(std::move(name), pos), source_(std::move(source)),
        destination_(std::move(destination)) {
  }

  DataFlow(uint64_t id, std::string name, std::shared_ptr<DfdNode> source,
      std::shared_ptr<DfdNode> destination, std::pair<float, float> pos)
      : DfdNode(id, std::move(name), pos), source_(std::move(source)),
        destination_(std::move(destination)) {
  }

  std::vector<std::shared_ptr<DataItem>> data_items_;
  std::shared_ptr<DfdNode> source_;
  std::shared_ptr<DfdNode> destination_;

  void Connect();

  [[nodiscard]] auto Serialize() const -> std::string override;

  [[nodiscard]] auto IsValid() const -> bool override {
    // Implement the IsValid method as needed
    // ...
    return true;
  }
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAFLOW_H_
