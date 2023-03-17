
#ifndef IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_MULTCANVASWINDOW_H_
#define IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_MULTCANVASWINDOW_H_

#include "EditorCanvas.h"
#include "signal/SignalHandel.h"

#include <memory>
#include <string>
#include <vector>

class MultCanvasWindow : public BaseWindow,
                         public std::enable_shared_from_this<MultCanvasWindow> {
public:
  explicit MultCanvasWindow(std::string title);
  void DrawContents() override;

  auto CreateNewCanvas(const std::string &title) -> int;

  void OpenCanvas(int canvas_id);

private:
  std::vector<std::shared_ptr<EditorCanvas>> canvas_;
  auto AddCanvas(const std::shared_ptr<EditorCanvas> &node_editor) -> int;

  bool has_build_callback_ = false;
  void InitCallback();
  int selected_canvas_id_ = 0; // 选择完之后会取负数，获取当前选择取绝对值

public:
  MultCanvasWindow(MultCanvasWindow &&) = default;
  MultCanvasWindow(const MultCanvasWindow &) = delete;
  auto operator=(MultCanvasWindow &&) -> MultCanvasWindow & = delete;
  auto operator=(const MultCanvasWindow &) -> MultCanvasWindow & = delete;
  ~MultCanvasWindow() override = default;
};

#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_MULTCANVASWINDOW_H_
