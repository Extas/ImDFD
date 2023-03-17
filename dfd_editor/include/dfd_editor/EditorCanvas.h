#ifndef IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_EDITORCANVAS_H_
#define IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_EDITORCANVAS_H_

#include <dfd_editor/NotificationWindow.h>
#include <imgui_node_editor.h>
#include <logging/Logger.h>
#include <node_model/NodeManager.h>
#include <node_model/element/Link.h>
#include <ui/BaseWindow.h>

#include <vector>
namespace ed = ax::NodeEditor;

class EditorCanvas : public BaseWindow {
public:
  explicit EditorCanvas(std::string title);

  void DrawContents() override;

  void SetCanvasCallback(
      std::function<void(int canvas_id)> navigate_to_canvas_callback,
      std::function<int(std::string title)> create_new_canvas_callback);

  [[nodiscard]] auto GetId() const -> int;

  bool open_ = false;

private:
  int canvas_id_ = 0;
  ed::EditorContext *context_ = nullptr;
  NodeManager node_manager_;
  LinkManager link_manager_;

  void Demo();
  void DrawNode() const;
  void DrawLink();
  void HandleInteractions();
  void HandleDelete();

  // Canvas state
  bool is_first_frame_ = true;
  auto IsFirstFrame() -> bool;
  void FirstFrame();

  static auto GetNewCanvasId() -> int;
  auto GetContext() -> ed::EditorContext *;

public:
  EditorCanvas();
  EditorCanvas(EditorCanvas &&) = delete;
  EditorCanvas(const EditorCanvas &) = delete;
  auto operator=(EditorCanvas &&) -> EditorCanvas & = delete;
  auto operator=(const EditorCanvas &) -> EditorCanvas & = delete;
  ~EditorCanvas() override;
};

#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_EDITORCANVAS_H_