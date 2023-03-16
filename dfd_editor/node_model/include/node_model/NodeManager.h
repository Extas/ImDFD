
#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODEMANAGER_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODEMANAGER_H_

#include "Node.h"

class NodeManager {
public:
  NodeManager() = default;

  void AddNode(std::string name, std::pair<float, float> position) {
    m_Nodes.emplace_back(std::move(name), position);
  }

  void AddNode(std::string name) {
    AddNode(std::move(name), std::make_pair(0, 0));
  }

  void AddInputPin(std::string name) {
    m_Nodes.back().AddInputPin(std::move(name));
  }

  void AddInputPin(std::string name, int node_id) {
    if (auto node = GetNode(node_id)) {
      if (node.has_value()) {
        node->get().AddInputPin(std::move(name));
      }
    }
  }

  void AddOutputPin(std::string name) {
    m_Nodes.back().AddOutputPin(std::move(name));
  }

  void AddOutputPin(std::string name, int node_id) {
    if (auto node = GetNode(node_id)) {
      if (node.has_value()) {
        node->get().AddOutputPin(std::move(name));
      }
    }
  }

  void RemoveNode(int node_id) {
    for (auto it = m_Nodes.begin(); it != m_Nodes.end(); ++it) {
      if (it->GetId() == node_id) {
        m_Nodes.erase(it);
        return;
      }
    }
  }

  [[nodiscard]] auto GetNode(int node_id)
      -> std::optional<std::reference_wrapper<Node>> {
    for (auto &node : m_Nodes) {
      if (node.GetId() == node_id) {
        return std::ref(node);
      }
    }
    return std::nullopt;
  }

  [[nodiscard]] auto GetPinById(int pin_id) const
      -> std::optional<std::reference_wrapper<const Pin>> {
    for (const auto &node : m_Nodes) {
      if (auto pin = node.GetPin(pin_id)) {
        return pin;
      }
    }
    return std::nullopt;
  }

  [[nodiscard]] auto GetInputPinById(int pin_id) const
      -> std::optional<std::reference_wrapper<const InPin>> {
    for (const auto &node : m_Nodes) {
      if (auto pin = node.GetInputPin(pin_id)) {
        return pin;
      }
    }
    return std::nullopt;
  }

  [[nodiscard]] auto GetOutputPinById(int pin_id) const
      -> std::optional<std::reference_wrapper<const OutPin>> {
    for (const auto &node : m_Nodes) {
      if (auto pin = node.GetOutputPin(pin_id)) {
        return pin;
      }
    }
    return std::nullopt;
  }

  [[nodiscard]] auto GetNodes() const -> const std::vector<Node> & {
    return m_Nodes;
  }

private:
  std::vector<Node> m_Nodes;
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODEMANAGER_H_
