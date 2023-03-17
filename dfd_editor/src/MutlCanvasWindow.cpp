#include <dfd_editor/MultCanvasWindow.h>

#include <imgui.h>
#include <logging/Logger.h>

MultCanvasWindow::MultCanvasWindow(std::string title)
    : BaseWindow(std::move(title)) {
}

void MultCanvasWindow::DrawContents() {
  static ImGuiTabBarFlags tab_bar_flags =
      ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_AutoSelectNewTabs;
  if (ImGui::BeginTabBar("NodeEditorTabBar", tab_bar_flags)) {

    // 不要用范围 for 循环遍历，读取的引用不正确
    for (size_t i = 0; i < canvas_.size(); ++i) {
      std::shared_ptr<EditorCanvas> &canvas = canvas_[i];

      ImGuiTabItemFlags tab_item_flags = ImGuiTabItemFlags_None;

      std::string tab_label = canvas->GetTitle();
      if (canvas->GetId() == selected_canvas_id_) {
        canvas->open_ = true;
        tab_item_flags |= ImGuiTabItemFlags_SetSelected;
        selected_canvas_id_ = -selected_canvas_id_;
      }

      if (ImGui::BeginTabItem(
              tab_label.c_str(), &canvas->open_, tab_item_flags)) {
        selected_canvas_id_ = -canvas->GetId();
        canvas->DrawContents();
        ImGui::EndTabItem();
      }
    }
    ImGui::EndTabBar();
  }
}

void MultCanvasWindow::InitCallback() {
  navigate_to_canvas_callback_ = [self = shared_from_this()](int canvas_id) {
    auto mult_canvas_window = std::static_pointer_cast<MultCanvasWindow>(self);

    // 查找具有给定ID的NodeEditor
    auto found_editor = std::find_if(mult_canvas_window->canvas_.begin(),
        mult_canvas_window->canvas_.end(),
        [canvas_id](const std::shared_ptr<EditorCanvas> &editor) {
          return editor->GetId() == canvas_id;
        });

    // 如果找到具有给定ID的NodeEditor，则将其设置为当前激活的选项卡
    if (found_editor != mult_canvas_window->canvas_.end()) {
      (*found_editor)->open_ = true;
    }
    mult_canvas_window->selected_canvas_id_ = canvas_id;
  };

  create_new_canvas_callback_ = [self = shared_from_this()](
                                    const std::string &title) {
    auto mult_canvas_window = std::static_pointer_cast<MultCanvasWindow>(self);
    return mult_canvas_window->CreateNewCanvas(title);
  };
}

auto MultCanvasWindow::CreateNewCanvas(
    const std::string &title = "New Data Flow Diagram") -> int {
  if (!has_build_callback_) {
    InitCallback();
    has_build_callback_ = true;
  }
  auto found_editor = std::find_if(canvas_.begin(), canvas_.end(),
      [title](const std::shared_ptr<EditorCanvas> &editor) {
        return editor->GetTitle() == title;
      });
  if (found_editor != canvas_.end()) {
    Logger::Info(("Canvas with title " + title + " already exists").c_str());
    return (*found_editor)->GetId();
  }
  return AddCanvas(std::make_shared<EditorCanvas>(title));
}

void MultCanvasWindow::OpenCanvas(int canvas_id) {
  auto found_editor = std::find_if(canvas_.begin(), canvas_.end(),
      [canvas_id](const std::shared_ptr<EditorCanvas> &editor) {
        return editor->GetId() == canvas_id;
      });

  if (found_editor != canvas_.end()) {
    (*found_editor)->open_ = true;
  }
}

auto MultCanvasWindow::AddCanvas(
    const std::shared_ptr<EditorCanvas> &node_editor) -> int {
  Logger::Trace("Adding node editor to window");
  canvas_.push_back(node_editor);
  canvas_.back()->SetCanvasCallback(
      navigate_to_canvas_callback_, create_new_canvas_callback_);
  int new_canvas_id = canvas_.back()->GetId();
  return new_canvas_id;
}
