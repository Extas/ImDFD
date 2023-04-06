#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODEMANAGER_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODEMANAGER_H_

#include "DataProcessNode.h"
#include "DataStorageNode.h"
#include "ExternalEntityNode.h"
#include "element/Node.h"
#include <signal/SignalHandel.h>

class Dfd;

class NodeManager {
public:
  NodeManager() = default;

  auto AddNode(std::shared_ptr<Node>) -> std::shared_ptr<Node>;
  auto ClearNodes() -> void;

  auto AddDataProcessNode(uint64_t node_id, std::string *name,
      std::pair<float, float> *position, std::string *description,
      uint64_t sub_dfd_id) -> std::shared_ptr<DataProcessNode>;
  auto AddExternalEntityNode(uint64_t node_id, std::string *name,
      std::pair<float, float> *position) -> std::shared_ptr<ExternalEntityNode>;
  auto AddDataStorageNode(uint64_t node_id, std::string *name,
      std::pair<float, float> *position) -> std::shared_ptr<DataStorageNode>;

  void RemoveNode(uint64_t node_id);

  [[nodiscard]] auto GetNode(uint64_t node_id)
      -> std::optional<std::reference_wrapper<Node>>;
  [[nodiscard]] auto GetNodeByPinId(uint64_t pin_id) const
      -> std::optional<std::reference_wrapper<Node>>;
  [[nodiscard]] auto GetPinType(uint64_t pin_id) const -> int;
  [[nodiscard]] auto GetInputPinById(uint64_t pin_id) const
      -> std::optional<std::reference_wrapper<const InPin>>;
  [[nodiscard]] auto GetOutputPinById(uint64_t pin_id) const
      -> std::optional<std::reference_wrapper<const OutPin>>;
  [[nodiscard]] auto GetNodes() const
      -> const std::vector<std::shared_ptr<Node>>;

private:
  std::vector<std::shared_ptr<Node>> nodes_;
};
#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODEMANAGER_H_
