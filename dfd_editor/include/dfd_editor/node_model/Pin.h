#ifndef PIN_HPP
#define PIN_HPP

#include "NodeObj.h"

#include <imgui_node_editor.h>
namespace ed = ax::NodeEditor;

#include <algorithm>
#include <string>
#include <vector>

class Node;
class Link;

class Pin : public NodeObj {
public:
  explicit Pin(std::string name) : NodeObj(std::move(name)) {
  }

  virtual void Draw(ed::PinKind pin_kind) const {
    ed::BeginPin(GetId(), pin_kind);
    ImGui::Text("%s", GetName().c_str());
    ed::EndPin();
    ImGui::SameLine();
  }

  ~Pin() override = default;

  Pin(const Pin &) = delete;
  Pin(Pin &&) noexcept = default;
  auto operator=(const Pin &) -> Pin & = delete;
  auto operator=(Pin &&) -> Pin & = delete;
};

class OutPin : public Pin {
public:
  using Pin::Pin;

  void Draw() const override {
    Pin::Draw(ed::PinKind::Output);
  }
};

class InPin : public Pin {
public:
  using Pin::Pin;

  void Draw() const override {
    Pin::Draw(ed::PinKind::Input);
  }

  // TODO(Pin): Add other functionality specific to in pin if necessary
};

#endif // PIN_HPP
