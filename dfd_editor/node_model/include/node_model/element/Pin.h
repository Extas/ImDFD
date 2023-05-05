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
  Pin(uint64_t pin_id, std::reference_wrapper<std::string> name)
      : DrawObj(pin_id, name) {
  }

  virtual void DrawCustom(ed::PinKind pin_kind) const {
    ImGui::Text("%s", GetName().get().c_str());
  }

private:
  inline static std::string default_name_ = "Pin";
};

class OutPin : public Pin {
public:
  explicit OutPin(
      uint64_t pin_id, std::reference_wrapper<std::string> name = default_name_)
      : Pin(pin_id, name) {
  }

  void Draw() override {
    Pin::DrawCustom(ed::PinKind::Output);
  }

private:
  inline static std::string default_name_ = "Out ->";
};

class InPin : public Pin {
public:
  explicit InPin(
      uint64_t pin_id, std::reference_wrapper<std::string> name = default_name_)
      : Pin(pin_id, name) {
  }

  void Draw() override {
    Pin::DrawCustom(ed::PinKind::Input);
  }

private:
  inline static std::string default_name_ = "-> In";
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_PIN_H_
