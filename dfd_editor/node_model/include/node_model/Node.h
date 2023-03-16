#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODE_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODE_H_

#include "NodeObj.h"
#include "Pin.h"

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

  void Draw() const override;

  ~Node() override = default;

  [[nodiscard]] auto GetInputPins() const -> const std::vector<InPin> & {
    return m_InputPins;
  }

  [[nodiscard]] auto GetOutputPins() const -> const std::vector<OutPin> & {
    return m_OutputPins;
  }

  [[nodiscard]] auto GetPin(int pin_id) const
      -> std::optional<std::reference_wrapper<const Pin>>;

  [[nodiscard]] auto GetInputPin(int pin_id) const
      -> std::optional<std::reference_wrapper<const InPin>>;

  [[nodiscard]] auto GetOutputPin(int pin_id) const
      -> std::optional<std::reference_wrapper<const OutPin>>;

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

  auto operator=(Node &&other) noexcept -> Node & {
    NodeObj::operator=(std::move(other));
    m_InputPins = std::move(other.m_InputPins);
    m_OutputPins = std::move(other.m_OutputPins);
    m_Position = other.m_Position;
    return *this;
  }
  Node(const Node &) = delete;
  auto operator=(const Node &) -> Node & = delete;
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODE_H_
