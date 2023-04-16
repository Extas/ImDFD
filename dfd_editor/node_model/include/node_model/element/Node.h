#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_ELEMENT_NODE_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_ELEMENT_NODE_H_

#include "DrawObj.h"
#include "Pin.h"

#include <examples/blueprints-example/utilities/builders.h>
#include <imgui_node_editor.h>
namespace ed = ax::NodeEditor;

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

class Node : public DrawObj {
public:
  Node(uint64_t node_id, std::reference_wrapper<std::string> name,
      std::reference_wrapper<std::pair<float, float>> position)
      : DrawObj(node_id, name), position_(position) {
  }

  void Draw() override;
  virtual void DrawCustomContent() const = 0;
  virtual void DrawCustomStyleStart() const = 0;
  virtual void DrawCustomStyleEnd() const = 0;

  [[nodiscard]] auto GetInputPins() const -> const std::vector<InPin> &;
  [[nodiscard]] auto GetOutputPins() const -> const std::vector<OutPin> &;
  [[nodiscard]] auto GetPin(uint64_t pin_id) const
      -> std::optional<std::reference_wrapper<const Pin>>;
  [[nodiscard]] auto GetInputPin(uint64_t pin_id) const
      -> std::optional<std::reference_wrapper<const InPin>>;
  [[nodiscard]] auto GetOutputPin(uint64_t pin_id) const
      -> std::optional<std::reference_wrapper<const OutPin>>;
  auto AddInputPin(uint64_t pin_id) -> InPin &;
  auto AddOutputPin(uint64_t pin_id) -> OutPin &;

  [[nodiscard]] auto GetPosition() const -> const std::pair<float, float> & {
    return position_.get();
  }

  void SetPosition(const std::pair<float, float> &new_position) {
    position_.get().first = new_position.first;
    position_.get().second = new_position.second;
  }

private:
  std::vector<InPin> input_pins_;
  std::vector<OutPin> output_pins_;
  std::reference_wrapper<std::pair<float, float>> position_;

  ed::Utilities::BlueprintNodeBuilder node_builder_;

public:
  Node(Node &&other) noexcept
      : DrawObj(std::move(other)), input_pins_(std::move(other.input_pins_)),
        output_pins_(std::move(other.output_pins_)),
        position_(other.position_) {
  }

  auto operator=(Node &&other) noexcept -> Node &;
  Node(const Node &) = delete;
  auto operator=(const Node &) -> Node & = delete;

  ~Node() override = default;
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_ELEMENT_NODE_H_
