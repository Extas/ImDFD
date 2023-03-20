#include <node_model/element/Node.h>
void Node::Draw() const {
  ed::BeginNode(GetId());
  ImGui::Text("%s", GetName().c_str());
  for (const auto &kPin : GetInputPins()) {
    kPin.Draw();
  }
  for (const auto &kPin : GetOutputPins()) {
    kPin.Draw();
  }
  DrawCustomContent();
  ed::EndNode();
}

auto Node::GetPin(int pin_id) const
    -> std::optional<std::reference_wrapper<const Pin>> {
  for (const auto &kPin : input_pins_) {
    if (kPin.GetId() == pin_id) {
      return std::cref(kPin);
    }
  }
  for (const auto &kPin : output_pins_) {
    if (kPin.GetId() == pin_id) {
      return std::cref(kPin);
    }
  }
  return std::nullopt;
}

auto Node::GetInputPin(int pin_id) const
    -> std::optional<std::reference_wrapper<const InPin>> {
  for (const auto &kPin : input_pins_) {
    if (kPin.GetId() == pin_id) {
      return std::cref(kPin);
    }
  }
  return std::nullopt;
}

auto Node::GetOutputPin(int pin_id) const
    -> std::optional<std::reference_wrapper<const OutPin>> {
  for (const auto &kPin : output_pins_) {
    if (kPin.GetId() == pin_id) {
      return std::cref(kPin);
    }
  }
  return std::nullopt;
}

auto Node::operator=(Node &&other) noexcept -> Node & {
  DrawObj::operator=(std::move(other));
  input_pins_ = std::move(other.input_pins_);
  output_pins_ = std::move(other.output_pins_);
  position_ = other.position_;
  return *this;
}
auto Node::AddInputPin(std::string *name) -> InPin & {
  input_pins_.emplace_back(name);
  return input_pins_.back();
}
auto Node::AddOutputPin(std::string *name) -> OutPin & {
  output_pins_.emplace_back(name);
  return output_pins_.back();
}
auto Node::GetInputPins() const -> const std::vector<InPin> & {
  return input_pins_;
}
auto Node::GetOutputPins() const -> const std::vector<OutPin> & {
  return output_pins_;
}
