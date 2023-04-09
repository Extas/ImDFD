#include <logging/Logger.h>
#include <node_model/element/Node.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

void ImGuiEx_BeginColumn() {
  ImGui::BeginGroup();
}

void ImGuiEx_NextColumn() {
  ImGui::EndGroup();
  ImGui::SameLine();
  ImGui::BeginGroup();
}

void ImGuiEx_EndColumn() {
  ImGui::EndGroup();
}

void Node::Draw() const {
  ed::BeginNode(GetId());
  ImGui::Text("%s", GetName().c_str());
  auto name_width = ImGui::CalcTextSize(GetName().c_str()).x;
  auto pin_width = ImGui::CalcTextSize("-> In").x;
  auto padding = std::max(name_width / 2 - pin_width, 0.0f);
  ImGui::BeginGroup();
  for (const auto &kPin : GetInputPins()) {
    kPin.Draw();
  }
  ImGui::EndGroup();
  ImGui::SameLine();

  ImGui::Dummy(ImVec2(padding, 0));
  ImGui::SameLine();

  ImGui::BeginGroup();
  DrawCustomContent();
  ImGui::EndGroup();
  ImGui::SameLine();
  ImGui::Dummy(ImVec2(padding, 0));
  ImGui::SameLine();

  ImGui::BeginGroup();
  for (const auto &kPin : GetOutputPins()) {
    kPin.Draw();
  }
  ImGui::EndGroup();

  ed::EndNode();
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
auto Node::AddInputPin(uint64_t pin_id, std::string *name) -> InPin & {
  input_pins_.emplace_back(pin_id, name);
  return input_pins_.back();
}
auto Node::AddOutputPin(uint64_t pin_id, std::string *name) -> OutPin & {
  output_pins_.emplace_back(pin_id, name);
  return output_pins_.back();
}
auto Node::GetInputPins() const -> const std::vector<InPin> & {
  return input_pins_;
}
auto Node::GetOutputPins() const -> const std::vector<OutPin> & {
  return output_pins_;
}
