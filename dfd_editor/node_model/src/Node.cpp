#include <node_model/element/Node.h>
void Node::Draw() const {
  ed::BeginNode(GetId());
  ImGui::Text("%s", GetName().c_str());
  for (const auto &pin : GetInputPins()) {
    pin.Draw();
  }
  for (const auto &pin : GetOutputPins()) {
    pin.Draw();
  }
  DrawCustomContent();
  ed::EndNode();
}

auto Node::GetPin(int pin_id) const
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

auto Node::GetInputPin(int pin_id) const
    -> std::optional<std::reference_wrapper<const InPin>> {
  for (const auto &pin : m_InputPins) {
    if (pin.GetId() == pin_id) {
      return std::cref(pin);
    }
  }
  return std::nullopt;
}

auto Node::GetOutputPin(int pin_id) const
    -> std::optional<std::reference_wrapper<const OutPin>> {
  for (const auto &pin : m_OutputPins) {
    if (pin.GetId() == pin_id) {
      return std::cref(pin);
    }
  }
  return std::nullopt;
}

auto Node::operator=(Node &&other) noexcept -> Node & {
  DrawObj::operator=(std::move(other));
  m_InputPins = std::move(other.m_InputPins);
  m_OutputPins = std::move(other.m_OutputPins);
  m_Position = other.m_Position;
  return *this;
}
auto Node::AddInputPin(std::string name) -> InPin & {
  m_InputPins.emplace_back(std::move(name));
  return m_InputPins.back();
}
auto Node::AddOutputPin(std::string name) -> OutPin & {
  m_OutputPins.emplace_back(std::move(name));
  return m_OutputPins.back();
}
auto Node::GetInputPins() const -> const std::vector<InPin> & {
  return m_InputPins;
}
auto Node::GetOutputPins() const -> const std::vector<OutPin> & {
  return m_OutputPins;
}
