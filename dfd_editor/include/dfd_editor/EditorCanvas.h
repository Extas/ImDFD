#ifndef IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_EDITORCANVAS_H_
#define IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_EDITORCANVAS_H_

#include <dfd_editor/CreateNewNodePopup.h>
#include <dfd_editor/NotificationWindow.h>
#include <dfd_model/Dfd.h>
#include <imgui_node_editor.h>
#include <logging/Logger.h>
#include <node_model/NodeManager.h>
#include <node_model/element/Link.h>
#include <signal/SignalHandel.h>
#include <ui/BaseWindow.h>

#include <vector>
namespace ed = ax::NodeEditor;

class EditorCanvas : public BaseWindow {
public:
  explicit EditorCanvas(const std::shared_ptr<Dfd> &dfd);

  void DrawContents() override;

  [[nodiscard]] auto GetId() const -> int64_t;

  bool open_ = false;

private:
  int64_t canvas_id_ = static_cast<int64_t>(0);
  ed::EditorContext *context_ = nullptr;
  std::shared_ptr<Dfd> dfd_;
  NodeManager node_manager_;
  LinkManager link_manager_;

  void DrawNode() const;
  void DrawLink();
  void HandleInteractions();
  void HandleDelete();
  void HandleRightClick();

  void ConnectSignals();

  // Canvas state
  bool is_first_frame_ = true;
  auto IsFirstFrame() -> bool;
  void FirstFrame();
  void UpdateDrawData();

  auto GetContext() -> ed::EditorContext *;

  CreateNewNodePopup create_new_node_popup_ = CreateNewNodePopup();

public:
  EditorCanvas(EditorCanvas &&) = delete;
  EditorCanvas(const EditorCanvas &) = delete;
  auto operator=(EditorCanvas &&) -> EditorCanvas & = delete;
  auto operator=(const EditorCanvas &) -> EditorCanvas & = delete;
  ~EditorCanvas() override;
  static void AddPin(const std::shared_ptr<DfdNode> &dfd_model_ptr,
      const std::shared_ptr<Node> &node);
  void AddLink(const std::shared_ptr<DataFlow> &kDataFlowPtr);
};

#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_EDITORCANVAS_H_
