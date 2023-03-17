#include <DearImGui.h>
#include <logging/Logger.h>

#include <dfd_editor/InfoWindow.h>
#include <dfd_editor/MultCanvasWindow.h>
#include <dfd_editor/NotificationWindow.h>
#include <memory>
#include <ui/BaseWindow.h>
#include <ui/MainMenuBar.h>

#include <filesystem>
void DearImGui::Init(GLFWwindow *window, const char *glsl_version) {
  Logger::Trace("Initializing Dear ImGui");
  IMGUI_CHECKVERSION();
  context_ = ImGui::CreateContext();

  IoConfig();

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
  ImGui::StyleColorsDark();

  auto info = ElementInfo("test", "test");
  AddWindow(std::make_shared<BaseWindow>("BaseWindow"));
  AddWindow(std::make_shared<InfoWindow>(info));
  auto mult_canvas_window =
      std::make_shared<MultCanvasWindow>("Node Editor Window");
  int new_canvas_1 = mult_canvas_window->CreateNewCanvas("Data Flow Diagram 1");
  mult_canvas_window->CreateNewCanvas("Data Flow Diagram 2");
  mult_canvas_window->OpenCanvas(new_canvas_1);
  AddWindow(mult_canvas_window);
  AddWindow(std::make_shared<NotificationWindow>());
}

void DearImGui::NewFrame() {
  // feed inputs to dear imgui, start new frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  ImGui::DockSpaceOverViewport();
}

void DearImGui::Draw() {

  ImGui::ShowDemoWindow();

  MainMenuBar menu_bar;
  menu_bar.Show();
  for (auto &window : windows_) {
    window->Draw();
  }
}

void DearImGui::Render() {
  // Render dear imgui into screen
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  // Update and Render additional Platform Windows
  auto &imgui_io = ImGui::GetIO();
  if ((imgui_io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) != 0) {
    GLFWwindow *backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
  }
}

void DearImGui::Shutdown() {
  Logger::Trace("Shutting down Dear ImGui");
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void DearImGui::IoConfig() {
  auto &imgui_io = ImGui::GetIO();

  // docking and multi-viewport enable
  imgui_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  imgui_io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
  // imgui_io.ConfigFlags |= ImGuiViewportFlags_NoDecoration;
  imgui_io.ConfigFlags |= ImGuiCol_DockingEmptyBg;

  // font
  constexpr float kFontSize = 26.0F;
  const auto fonts_dir =
      std::filesystem::current_path().parent_path() / "data" / "fonts";
  if (std::filesystem::exists(fonts_dir)) {
    for (const auto &font_path :
        std::filesystem::directory_iterator(fonts_dir)) {
      if (font_path.path().extension() == ".ttf") {
        imgui_io.Fonts->AddFontFromFileTTF(font_path.path().string().data(),
            kFontSize, nullptr, imgui_io.Fonts->GetGlyphRangesChineseFull());
        break;
      }
    }
  }
}

void DearImGui::AddWindow(std::shared_ptr<BaseWindow> window) {
  windows_.push_back(std::move(window));
}
