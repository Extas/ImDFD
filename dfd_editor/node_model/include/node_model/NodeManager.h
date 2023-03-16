
#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODEMANAGER_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODEMANAGER_H_

#include "DataProcessNode.h"
#include "Node.h"

class NodeManager {
public:
  NodeManager() = default;

  void AddNode(std::string name, std::pair<float, float> position) {
    nodes_.push_back(std::make_unique<Node>(std::move(name), position));
  }

  void AddNode(std::string name) {
    AddNode(std::move(name), std::make_pair(0, 0));
  }

  void AddDataProcessNode(const std::string &name,
      std::pair<float, float> position, const DataProcess &data_processing) {
    nodes_.push_back(
        std::make_unique<DataProcessNode>(name, position, data_processing));
  }

  void AddInputPin(std::string name) {
    nodes_.back()->AddInputPin(std::move(name));
  }

  void AddInputPin(std::string name, int node_id) {
    if (auto node = GetNode(node_id)) {
      if (node.has_value()) {
        node->get().AddInputPin(std::move(name));
      }
    }
  }

  void AddOutputPin(std::string name) {
    nodes_.back()->AddOutputPin(std::move(name));
  }

  void AddOutputPin(std::string name, int node_id) {
    if (auto node = GetNode(node_id)) {
      if (node.has_value()) {
        node->get().AddOutputPin(std::move(name));
      }
    }
  }

  void RemoveNode(int node_id) {
    for (auto &node_ptr : nodes_) {
      if (node_ptr->GetId() == node_id) {
        node_ptr = std::move(nodes_.back());
        nodes_.pop_back();
        return;
      }
    }
  }

  // 使用GetNode方法的地方，需要根据节点的类型进行相应的类型转换。可以使用dynamic_cast来实现。
  [[nodiscard]] auto GetNode(int node_id)
      -> std::optional<std::reference_wrapper<Node>> {
    for (auto &node_ptr : nodes_) {
      if (node_ptr->GetId() == node_id) {
        return std::ref(*node_ptr);
      }
    }
    return std::nullopt;
  }

  [[nodiscard]] auto GetPinById(int pin_id) const
      -> std::optional<std::reference_wrapper<const Pin>> {
    for (const auto &kNodePtr : nodes_) {
      if (auto pin = kNodePtr->GetPin(pin_id)) {
        return pin;
      }
    }
    return std::nullopt;
  }

  [[nodiscard]] auto GetInputPinById(int pin_id) const
      -> std::optional<std::reference_wrapper<const InPin>> {
    for (const auto &kNodePtr : nodes_) {
      if (auto pin = kNodePtr->GetInputPin(pin_id)) {
        return pin;
      }
    }
    return std::nullopt;
  }

  [[nodiscard]] auto GetOutputPinById(int pin_id) const
      -> std::optional<std::reference_wrapper<const OutPin>> {
    for (const auto &kNodePtr : nodes_) {
      if (auto pin = kNodePtr->GetOutputPin(pin_id)) {
        return pin;
      }
    }
    return std::nullopt;
  }

  [[nodiscard]] auto GetNodes() const
      -> const std::vector<std::unique_ptr<Node>> & {
    return nodes_;
  }

private:
  std::vector<std::unique_ptr<Node>> nodes_;
};
#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODEMANAGER_H_
