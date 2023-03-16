
#ifndef IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODEEDITORWINDOW_H_
#define IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODEEDITORWINDOW_H_

#include "NodeEditor.h"
#include <memory>
#include <string>
#include <vector>

class NodeEditorWindow : public BaseWindow {
public:
  explicit NodeEditorWindow(std::string title);
  void DrawContents() override;

  void AddNodeEditor(const std::shared_ptr<NodeEditor> &node_editor);

private:
  std::vector<std::shared_ptr<NodeEditor>> node_editors_;

public:
  NodeEditorWindow(NodeEditorWindow &&) = default;
  NodeEditorWindow(const NodeEditorWindow &) = delete;
  auto operator=(NodeEditorWindow &&) -> NodeEditorWindow & = delete;
  auto operator=(const NodeEditorWindow &) -> NodeEditorWindow & = delete;
  ~NodeEditorWindow() override = default;
};

#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODEEDITORWINDOW_H_
