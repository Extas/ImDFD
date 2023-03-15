#ifndef NODE_H
#define NODE_H

#include "NodeObj.h"
#include "Pin.h"
#include "dfd_editor/node_model/Pin.h"

#include <imgui_node_editor.h>
namespace ed = ax::NodeEditor;

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

class Node : public NodeObj {
public:
  Node(std::string name, std::pair<float, float> position)
      : NodeObj(std::move(name)), m_Position(position) {
  }

  void Draw() const override {
    ed::BeginNode(GetId());
    ImGui::Text("%s", GetName().c_str());
    for (const auto &pin : GetInputPins()) {
      pin.Draw();
    }
    for (const auto &pin : GetOutputPins()) {
      pin.Draw();
    }
    ed::EndNode();
  }

  ~Node() override = default;

  [[nodiscard]] auto GetInputPins() const -> const std::vector<InPin> & {
    return m_InputPins;
  }

  [[nodiscard]] auto GetOutputPins() const -> const std::vector<OutPin> & {
    return m_OutputPins;
  }

  [[nodiscard]] auto GetPin(int pin_id) const
      -> std::optional<std::reference_wrapper<const Pin>> {
    for (const auto &pin : m_InputPins) {
      if (pin.GetId() == pin_id) {
        return std::cref(pin);
      }
    }
    for (const auto &pin : m_OutputPins) {
      if (pin.GetId() == pin_id) {
        return std::cref(pin);
      }
    }
    return std::nullopt;
  }

  [[nodiscard]] auto GetInputPin(int pin_id) const
      -> std::optional<std::reference_wrapper<const InPin>> {
    for (const auto &pin : m_InputPins) {
      if (pin.GetId() == pin_id) {
        return std::cref(pin);
      }
    }
    return std::nullopt;
  }

  [[nodiscard]] auto GetOutputPin(int pin_id) const
      -> std::optional<std::reference_wrapper<const OutPin>> {
    for (const auto &pin : m_OutputPins) {
      if (pin.GetId() == pin_id) {
        return std::cref(pin);
      }
    }
    return std::nullopt;
  }

  auto AddInputPin(std::string name) -> InPin & {
    m_InputPins.emplace_back(std::move(name));
    return m_InputPins.back();
  }

  auto AddOutputPin(std::string name) -> OutPin & {
    m_OutputPins.emplace_back(std::move(name));
    return m_OutputPins.back();
  }

  [[nodiscard]] auto GetPosition() const -> const std::pair<float, float> & {
    return m_Position;
  }

private:
  std::vector<InPin> m_InputPins;
  std::vector<OutPin> m_OutputPins;
  std::pair<float, float> m_Position;

public:
  Node(Node &&other) noexcept
      : NodeObj(std::move(other)), m_InputPins(std::move(other.m_InputPins)),
        m_OutputPins(std::move(other.m_OutputPins)),
        m_Position(other.m_Position) {
  }

  auto operator=(Node &&other) -> Node & {
    NodeObj::operator=(std::move(other));
    m_InputPins = std::move(other.m_InputPins);
    m_OutputPins = std::move(other.m_OutputPins);
    m_Position = other.m_Position;
    return *this;
  }
  Node(const Node &) = delete;
  auto operator=(const Node &) -> Node & = delete;
};

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

#endif // NODE_H
