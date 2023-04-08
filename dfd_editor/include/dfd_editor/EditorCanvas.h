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

  void NavigateToElement(uint64_t element_id);
  void ResetZoom();

  [[nodiscard]] auto GetId() const -> int64_t;

  bool open_ = false;

private:
  auto GetOrInitContext() -> ed::EditorContext *;
  void LoadDrawData();
  auto IsFirstFrame() -> bool;
  void FirstFrame();
  void DrawNode() const;
  void DrawLink();
  void HandleInteractions();
  void HandleDelete();
  void UpdateSelected();

  int64_t canvas_id_ = static_cast<int64_t>(0);
  ed::EditorContext *context_ = nullptr;
  ed::Config config_;

  std::shared_ptr<Dfd> dfd_;
  NodeManager node_manager_;
  LinkManager link_manager_;

  std::vector<ed::NodeId> selected_nodes_;
  std::vector<ed::LinkId> selected_links_;

  CreateNewNodePopup create_new_node_popup_ = CreateNewNodePopup(GetId());

  void HandleRightClick();
  void LoadLinkFromFlow(const std::shared_ptr<DataFlow> &data_flow_ptr);

  void ConnectSignals();
  bool is_first_frame_ = true;

public:
  EditorCanvas(EditorCanvas &&) = delete;
  EditorCanvas(const EditorCanvas &) = delete;
  auto operator=(EditorCanvas &&) -> EditorCanvas & = delete;
  auto operator=(const EditorCanvas &) -> EditorCanvas & = delete;

  ~EditorCanvas() override;
};

#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_EDITORCANVAS_H_
