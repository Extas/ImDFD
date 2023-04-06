#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAFLOW_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAFLOW_H_

#include "DataItem.h"
#include "DfdNode.h"

#include <memory>
#include <vector>

class DfdNode;

class DataFlow : public DfdNode, public std::enable_shared_from_this<DataFlow> {
public:

  static auto Create(uint64_t id, std::string name,
      std::shared_ptr<DfdNode> source,
      std::shared_ptr<DfdNode> destination,
      std::pair<float, float> pos) -> std::shared_ptr<DataFlow>;

  static auto Create(std::string name,
      std::shared_ptr<DfdNode> source, std::shared_ptr<DfdNode> destination,
      std::pair<float, float> pos) -> std::shared_ptr<DataFlow>;

  auto HasNode(uint64_t node_id) const -> bool;
  void Connect();

  [[nodiscard]] auto Serialize() const -> nlohmann::json override;

  [[nodiscard]] auto IsValid() const -> bool override;

  std::vector<std::shared_ptr<DataItem>> data_items_;
  std::shared_ptr<DfdNode> source_;
  std::shared_ptr<DfdNode> destination_;

private:
  DataFlow(std::string name, std::shared_ptr<DfdNode> source,
      std::shared_ptr<DfdNode> destination, std::pair<float, float> pos);

  DataFlow(uint64_t id, std::string name, std::shared_ptr<DfdNode> source,
      std::shared_ptr<DfdNode> destination, std::pair<float, float> pos);
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAFLOW_H_
