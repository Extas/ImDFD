#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_PIN_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_PIN_H_

#include "DrawObj.h"

#include <imgui_node_editor.h>
namespace ed = ax::NodeEditor;

#include <algorithm>
#include <string>
#include <vector>

class Node;
class Link;

class Pin : public DrawObj {
public:
  explicit Pin(std::string name) : DrawObj(std::move(name)) {
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

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_PIN_H_
