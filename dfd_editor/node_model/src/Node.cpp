#include <logging/Logger.h>
#include <node_model/element/Node.h>
#define IMGUI_DEFINE_MATH_OPERATORS

void Node::Draw() {
  ed::PushStyleColor(ed::StyleColor_NodeBg, ImColor(75, 75, 75, 200));
  DrawCustomStyleStart();
  node_builder_.Begin(GetId());

  node_builder_.Header();

  ImGui::Spring(0);
  ImGui::TextUnformatted(GetName().get().c_str());
  ImGui::Spring(1);
  ImGui::Dummy(ImVec2(0, 28));

  node_builder_.EndHeader();

  for (auto &input : input_pins_) {
    node_builder_.Input(input.GetId());
    input.Draw();
    node_builder_.EndInput();
  }

  node_builder_.Middle();
  DrawCustomContent();

  for (auto &output : output_pins_) {
    node_builder_.Output(output.GetId());
    output.Draw();
    node_builder_.EndOutput();
  }
  node_builder_.End();
  DrawCustomStyleEnd();
  ed::PopStyleColor();
}

auto Node::GetPin(uint64_t pin_id) const
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

auto Node::GetInputPin(uint64_t pin_id) const
    -> std::optional<std::reference_wrapper<const InPin>> {
  for (const auto &kPin : input_pins_) {
    if (kPin.GetId() == pin_id) {
      return std::cref(kPin);
    }
  }
  return std::nullopt;
}

auto Node::GetOutputPin(uint64_t pin_id) const
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
auto Node::AddInputPin(uint64_t pin_id) -> InPin & {
  input_pins_.emplace_back(pin_id);
  return input_pins_.back();
}
auto Node::AddOutputPin(uint64_t pin_id) -> OutPin & {
  output_pins_.emplace_back(pin_id);
  return output_pins_.back();
}
auto Node::GetInputPins() const -> const std::vector<InPin> & {
  return input_pins_;
}
auto Node::GetOutputPins() const -> const std::vector<OutPin> & {
  return output_pins_;
}
