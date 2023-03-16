#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODE_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODE_H_

#include "DrawObj.h"
#include "Pin.h"

#include <imgui_node_editor.h>
namespace ed = ax::NodeEditor;

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

class Node : public DrawObj {
public:
  Node(std::string name, std::pair<float, float> position)
      : DrawObj(std::move(name)), m_Position(position) {
  }

  void Draw() const override;
  virtual void DrawCustomContent() const {
  }

  [[nodiscard]] auto GetInputPins() const -> const std::vector<InPin> &;
  [[nodiscard]] auto GetOutputPins() const -> const std::vector<OutPin> &;
  [[nodiscard]] auto GetPin(int pin_id) const
      -> std::optional<std::reference_wrapper<const Pin>>;
  [[nodiscard]] auto GetInputPin(int pin_id) const
      -> std::optional<std::reference_wrapper<const InPin>>;
  [[nodiscard]] auto GetOutputPin(int pin_id) const
      -> std::optional<std::reference_wrapper<const OutPin>>;
  auto AddInputPin(std::string name) -> InPin &;
  auto AddOutputPin(std::string name) -> OutPin &;

  [[nodiscard]] auto GetPosition() const -> const std::pair<float, float> & {
    return m_Position;
  }
  void SetPosition(std::pair<float, float> position) {
    m_Position = position;
  }

private:
  std::vector<InPin> m_InputPins;
  std::vector<OutPin> m_OutputPins;
  std::pair<float, float> m_Position;

public:
  Node(Node &&other) noexcept
      : DrawObj(std::move(other)), m_InputPins(std::move(other.m_InputPins)),
        m_OutputPins(std::move(other.m_OutputPins)),
        m_Position(other.m_Position) {
  }

  auto operator=(Node &&other) noexcept -> Node &;
  Node(const Node &) = delete;
  auto operator=(const Node &) -> Node & = delete;

  ~Node() override = default;
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODE_H_
