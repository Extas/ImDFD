#ifndef NODEEDITORWINDOW_H
#define NODEEDITORWINDOW_H

#include <ui/BaseWindow.h>

#include <imgui_node_editor.h>
namespace ed = ax::NodeEditor;

class NodeEditerWindow : public BaseWindow {
public:
  explicit NodeEditerWindow(std::string title);

  void DrawContents() override;
  ~NodeEditerWindow() override;

private:
  ed::EditorContext *kMContext = ed::CreateEditor();

  NodeEditerWindow() = default;
  NodeEditerWindow(NodeEditerWindow &&) = delete;
  NodeEditerWindow(const NodeEditerWindow &) = delete;
  auto operator=(NodeEditerWindow &&) -> NodeEditerWindow & = delete;
  auto operator=(const NodeEditerWindow &) -> NodeEditerWindow & = delete;
};

#endif // NODEEDITORWINDOW_H
