#include <dfd_editor/MultCanvasWindow.h>

#include <imgui.h>
#include <logging/Logger.h>
#include <string>

MultCanvasWindow::MultCanvasWindow(std::string title)
    : BaseWindow(std::move(title)) {
}

void MultCanvasWindow::LoadDfd(const std::shared_ptr<Dfd> &dfd) {
  Logger::Trace("[MultCanvasWindow] Loading DFD into NodeEditor ({}: {})",
      dfd->GetElementId(), dfd->GetName());
  dfds_.clear();
  canvas_.clear();
  CreateNewCanvas(dfd);
  dfds_.push_back(dfd);

  selected_canvas_id_ = static_cast<int64_t>(dfd->GetElementId());
}

void MultCanvasWindow::DrawContents() {
  static ImGuiTabBarFlags tab_bar_flags =
      ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_AutoSelectNewTabs;
  if (ImGui::BeginTabBar("NodeEditorTabBar", tab_bar_flags)) {

    for (size_t i = 0; i < canvas_.size(); ++i) {
      std::shared_ptr<EditorCanvas> &canvas = canvas_[i];

      ImGuiTabItemFlags tab_item_flags = ImGuiTabItemFlags_None;

      std::string tab_label =
          canvas->GetTitle() + "##" + std::to_string(canvas->GetId());
      if (canvas->GetId() == selected_canvas_id_) {
        canvas->open_ = true;
        tab_item_flags |= ImGuiTabItemFlags_SetSelected;
        selected_canvas_id_ = -selected_canvas_id_;
      }

      if (ImGui::BeginTabItem(
              tab_label.c_str(), &canvas->open_, tab_item_flags)) {
        canvas->DrawContents();
        ImGui::EndTabItem();
      }
    }
    ImGui::EndTabBar();
  }
}

void MultCanvasWindow::ConnectSignal() {
  SignalHandel::Instance().navigate_sub_diagram_onclick_.connect(
      [self = shared_from_this()](int canvas_id) {
        auto mult_canvas_window =
            std::static_pointer_cast<MultCanvasWindow>(self);

        auto found_editor = std::find_if(mult_canvas_window->canvas_.begin(),
            mult_canvas_window->canvas_.end(),
            [canvas_id](const std::shared_ptr<EditorCanvas> &editor) {
              return editor->GetId() == canvas_id;
            });

        if (found_editor != mult_canvas_window->canvas_.end()) {
          (*found_editor)->open_ = true;
        }
        mult_canvas_window->selected_canvas_id_ = canvas_id;
      });

  SignalHandel::Instance().create_new_dfd_.connect(
      [self = shared_from_this()](const std::shared_ptr<Dfd> &sub_dfd) {
        auto mult_canvas_window =
            std::static_pointer_cast<MultCanvasWindow>(self);
        mult_canvas_window->CreateNewCanvas(sub_dfd);
      });
}

auto MultCanvasWindow::CreateNewCanvas(const std::shared_ptr<Dfd> &dfd)
    -> int64_t {
  if (!has_connect_signal_) {
    ConnectSignal();
    has_connect_signal_ = true;
  }

  int64_t canvas_id = dfd->GetElementId();
  auto found_editor = std::find_if(canvas_.begin(), canvas_.end(),
      [canvas_id](const std::shared_ptr<EditorCanvas> &editor) {
        return editor->GetId() == canvas_id;
      });
  if (found_editor != canvas_.end()) {
    return (*found_editor)->GetId();
  }

  return AddCanvas(std::make_shared<EditorCanvas>(dfd));
}

auto MultCanvasWindow::AddCanvas(
    const std::shared_ptr<EditorCanvas> &editor_canvas) -> int64_t {
  canvas_.push_back(editor_canvas);
  int64_t new_canvas_id = canvas_.back()->GetId();
  Logger::Trace("[MultCanvasWindow] New canvas added ({}: {})", new_canvas_id,
      editor_canvas->GetTitle());
  return new_canvas_id;
}
