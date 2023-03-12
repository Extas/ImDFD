#ifndef NODE_H
#define NODE_H

#include "NodeObj.h"
#include "Pin.h"
#include <string>
#include <vector>

class Node : public NodeObj {
public:
  explicit Node(std::string name) : NodeObj(std::move(name)) {
  }

  explicit Node(std::string name, std::pair<float, float> position)
      : NodeObj(std::move(name)), m_Position(position) {
  }

  ~Node() override = default;

  [[nodiscard]] auto GetInputPins() const -> const std::vector<InPin> & {
    return m_InputPins;
  }

  [[nodiscard]] auto GetOutputPins() const -> const std::vector<OutPin> & {
    return m_OutputPins;
  }

  auto AddInputPin(std::string name) -> InPin & {
    m_InputPins.emplace_back(std::move(name));
    m_InputPins.back().SetParentNode(this);
    return m_InputPins.back();
  }

  auto AddOutputPin(std::string name) -> OutPin & {
    m_OutputPins.emplace_back(std::move(name));
    m_OutputPins.back().SetParentNode(this);
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

  Node(const Node &) = delete;
  auto operator=(Node &&) -> Node & = delete;
  auto operator=(const Node &) -> Node & = delete;
};

#endif // NODE_H
