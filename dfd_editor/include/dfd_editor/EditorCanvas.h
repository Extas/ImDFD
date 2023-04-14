#ifndef IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_EDITORCANVAS_H_
#define IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_EDITORCANVAS_H_

#include <cstdint>
#include <dfd_editor/NotificationWindow.h>
#include <dfd_model/Dfd.h>
#include <imgui_node_editor.h>
#include <logging/Logger.h>
#include <node_model/NodeManager.h>
#include <node_model/element/Link.h>
#include <signal/SignalHandel.h>
#include <ui/BaseWindow.h>
#include <ui/Widgets.h>

#include <vector>
namespace ed = ax::NodeEditor;
namespace widgets = imdfd::ui::widgets;

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

  void HandleCreateNewLink();
  void HandleRightClick();
  void ConnectSignals();
  bool is_first_frame_ = true;

  void Navigate();
  uint64_t navigate_id_ = -1;
  bool need_navigate_ = false;

  void LoadDataProcessNodes();
  void LoadExternalEntityNodes();
  void LoadDataStorageNodes();
  void LoadDataFlowLinks();

  ed::NodeId context_node_id_;
  widgets::MenuItemListPopup delete_node_popup_ = widgets::MenuItemListPopup(
      "Delete Node", std::map<uint64_t, std::string>{{0, "Delete"}},
      [this](uint64_t index, std::pair<float, float> pos) {
        if (index == 0) {
          auto node_id = context_node_id_.Get();
          dfd_->DeleteNode(node_id);
        }
      });

  widgets::MenuItemListPopup create_new_node_list_popup_ =
      widgets::MenuItemListPopup("Create New Node",
          std::map<uint64_t, std::string>{
              {0, "Data Process"}, {1, "External Entity"}, {2, "Data Store"}},
          [this](uint64_t index, std::pair<float, float> pos) {
            switch (index) {
            case 0: {
              Logger::Trace("[MenuItemListPopup {}] MenuItem {} Clicked",
                  canvas_id_, "Data Process");
              SignalHandel::Instance().create_new_node_(
                  canvas_id_, "DataProcess", pos);
              break;
            }
            case 1: {
              Logger::Trace("[MenuItemListPopup {}] MenuItem {} Clicked",
                  canvas_id_, "External Entity");
              SignalHandel::Instance().create_new_node_(
                  canvas_id_, "ExternalEntity", pos);
              break;
            }
            case 2: {
              Logger::Trace("[MenuItemListPopup {}] MenuItem {} Clicked",
                  canvas_id_, "Data Store");
              SignalHandel::Instance().create_new_node_(
                  canvas_id_, "DataStorage", pos);
              break;
            }
            default:
              break;
            }
          });

public:
  EditorCanvas(EditorCanvas &&) = delete;
  EditorCanvas(const EditorCanvas &) = delete;

  auto operator=(EditorCanvas &&) -> EditorCanvas & = delete;
  auto operator=(const EditorCanvas &) -> EditorCanvas & = delete;
  ~EditorCanvas() override;
};

#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_EDITORCANVAS_H_
