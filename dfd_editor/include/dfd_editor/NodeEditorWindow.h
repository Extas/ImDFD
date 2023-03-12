#ifndef NODEEDITORWINDOW_H
#define NODEEDITORWINDOW_H

#include "dfd_editor/node_model/Link.h"
#include "node_model/Link.h"
#include "node_model/Node.h"
#include "spdlog/fmt/bundled/core.h"
#include <imgui_node_editor.h>
#include <logging/Logger.h>
#include <ui/BaseWindow.h>
#include <vector>
namespace ed = ax::NodeEditor;

class NodeEditorWindow : public BaseWindow {
public:
  explicit NodeEditorWindow(std::string title);

  void AddNodeObj(NodeObj &&nodeObj);
  void AddLink(Link &&link);

  void DrawContents() override;
  ~NodeEditorWindow() override;

private:
  int m_uniqueId = 0;
  ed::EditorContext *m_Context = GetContext();
  std::vector<Node> m_Nodes;
  LinkManager m_LinkManager;

  void demo();
  void DrawNode();
  void DrawLink();

  static auto IsFirstFrame() -> bool {
    static bool isFirstFrame = true;
    if (isFirstFrame) {
      isFirstFrame = false;
      return true;
    }
    return false;
  }

  static auto GetContext() -> ed::EditorContext * {
    static bool isInitialized = false;
    static ed::EditorContext *context = nullptr;
    if (isInitialized) {
      return context;
    }
    Logger::Trace("Initializing context");
    context = ed::CreateEditor();
    isInitialized = true;
    return context;
  }

  void FirstFrame();

public:
  NodeEditorWindow();
  NodeEditorWindow(NodeEditorWindow &&) = delete;
  NodeEditorWindow(const NodeEditorWindow &) = delete;
  auto operator=(NodeEditorWindow &&) -> NodeEditorWindow & = delete;
  auto operator=(const NodeEditorWindow &) -> NodeEditorWindow & = delete;
};

#endif // NODEEDITORWINDOW_H
