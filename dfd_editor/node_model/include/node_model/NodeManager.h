
#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODEMANAGER_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODEMANAGER_H_

#include "DataProcessNode.h"
#include "element/Node.h"

class NodeManager {
public:
  NodeManager() = default;

  void SetOpenDFDCallback(std::function<void()> callback);

  void AddNode(std::string name, std::pair<float, float> position);
  void AddNode(std::string name);
  void AddDataProcessNode(const std::string &name,
      std::pair<float, float> position, const DataProcess &data_processing);
  void AddInputPin(std::string name);
  void AddInputPin(std::string name, int node_id);
  void AddOutputPin(std::string name);
  void AddOutputPin(std::string name, int node_id);

  void RemoveNode(int node_id);

  // 使用GetNode方法的地方，需要根据节点的类型进行相应的类型转换。可以使用dynamic_cast来实现。
  [[nodiscard]] auto GetNode(int node_id)
      -> std::optional<std::reference_wrapper<Node>>;
  [[nodiscard]] auto GetPinById(int pin_id) const
      -> std::optional<std::reference_wrapper<const Pin>>;
  [[nodiscard]] auto GetInputPinById(int pin_id) const
      -> std::optional<std::reference_wrapper<const InPin>>;
  [[nodiscard]] auto GetOutputPinById(int pin_id) const
      -> std::optional<std::reference_wrapper<const OutPin>>;
  [[nodiscard]] auto GetNodes() const
      -> const std::vector<std::unique_ptr<Node>> &;

private:
  std::vector<std::unique_ptr<Node>> nodes_;
  std::function<void()> open_dfd_callback_;
};
#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODEMANAGER_H_
