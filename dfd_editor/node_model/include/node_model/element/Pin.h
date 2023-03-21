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
  Pin(uint64_t pin_id, std::string *name) : DrawObj(pin_id, name) {
  }

  virtual void DrawCustom(ed::PinKind pin_kind) const {
    ed::BeginPin(GetId(), pin_kind);
    ImGui::Text("%s", GetName().c_str());
    ed::EndPin();
    ImGui::SameLine();
  }
};

class OutPin : public Pin {
public:
  explicit OutPin(std::string *name) : Pin(0, name) {
  }

  void Draw() const override {
    Pin::DrawCustom(ed::PinKind::Output);
  }
};

class InPin : public Pin {
public:
  explicit InPin(std::string *name) : Pin(0, name) {
  }

  void Draw() const override {
    Pin::DrawCustom(ed::PinKind::Input);
  }
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_PIN_H_
