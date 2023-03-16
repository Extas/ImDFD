#ifndef DFD_EDITOR_NODEEDITOR_H
#define DFD_EDITOR_NODEEDITOR_H

#include <dfd_editor/NotificationWindow.h>
#include <imgui_node_editor.h>
#include <logging/Logger.h>
#include <node_model/Link.h>
#include <node_model/NodeManager.h>
#include <ui/BaseWindow.h>

#include <vector>
namespace ed = ax::NodeEditor;

class NodeEditor : public BaseWindow {
public:
  explicit NodeEditor(std::string title);

  void AddNode(std::string name, std::pair<float, float> position);
  void DrawContents() override;

private:
  NodeManager node_manager_;
  LinkManager link_manager_;

  bool active_ = false;
  bool is_first_frame_ = true;
  ed::EditorContext *context_ = nullptr;

  void Demo();
  void DrawNode();
  void DrawLink();
  void HandleInteractions();
  void HandleDelete();

  auto IsFirstFrame() -> bool;
  auto GetContext() -> ed::EditorContext *;
  void SetActive(bool active);
  void FirstFrame();

public:
  NodeEditor();
  NodeEditor(NodeEditor &&) = delete;
  NodeEditor(const NodeEditor &) = delete;
  auto operator=(NodeEditor &&) -> NodeEditor & = delete;
  auto operator=(const NodeEditor &) -> NodeEditor & = delete;
  ~NodeEditor() override;
};

#endif // DFD_EDITOR_NODEEDITOR_H
