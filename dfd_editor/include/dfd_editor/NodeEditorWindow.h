#ifndef NODEEDITORWINDOW_H
#define NODEEDITORWINDOW_H

#include "dfd_editor/node_model/Node.h"
#include "node_model/Link.h"
#include "node_model/Node.h"

#include <dfd_editor/NotificationWindow.h>
#include <imgui_node_editor.h>
#include <logging/Logger.h>
#include <ui/BaseWindow.h>

#include <vector>
namespace ed = ax::NodeEditor;

class NodeEditorWindow : public BaseWindow {
public:
  explicit NodeEditorWindow(std::string title);

  void AddNode(std::string name, std::pair<float, float> position);
  void DrawContents() override;

private:
  ed::EditorContext *m_context_ = GetContext();
  NodeManager node_manager_;
  LinkManager m_link_manager_;

  void Demo();
  void DrawNode();
  void DrawLink();
  void HandleInteractions();
  void HandleDelete();

  static auto IsFirstFrame() -> bool;
  static auto GetContext() -> ed::EditorContext *;
  void FirstFrame();

public:
  NodeEditorWindow();
  NodeEditorWindow(NodeEditorWindow &&) = delete;
  NodeEditorWindow(const NodeEditorWindow &) = delete;
  auto operator=(NodeEditorWindow &&) -> NodeEditorWindow & = delete;
  auto operator=(const NodeEditorWindow &) -> NodeEditorWindow & = delete;
  ~NodeEditorWindow() override;
};

#endif // NODEEDITORWINDOW_H
