#include <DearImGui.h>
#include <logging/Logger.h>

#include <dfd_editor/InfoWindow.h>
#include <dfd_editor/MultCanvasWindow.h>
#include <dfd_editor/NotificationWindow.h>
#include <dfd_model/Dfd.h>
#include <memory>
#include <ui/BaseWindow.h>

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
  AddWindow(std::make_shared<BaseWindow>("test"));
  AddWindow(std::make_shared<InfoWindow>(info));
  AddWindow(std::make_shared<NotificationWindow>());
  Logger::Info("Welcome to the ImDFD");

  auto mult_canvas_window =
      std::make_shared<MultCanvasWindow>("Node Editor Window");
  AddWindow(mult_canvas_window);

  auto test_dfd = std::make_shared<Dfd>("test_dfd");
  test_dfd->CreateTestData();
  auto test_seri = test_dfd->Serialize();
  auto test_dfd2 = Dfd::DeSerialize(test_seri);
  mult_canvas_window->LoadDfd(test_dfd2);
  auto str = test_dfd->Serialize();
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

  menu_bar_.Show();

  if (menu_bar_.GetFileDialog().HasSelected()) {
    // std::cout << "Selected filename: " <<
    // menu_bar_.GetFileDialog().GetSelected().string() << std::endl;
    menu_bar_.GetFileDialog().ClearSelected();
  }

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
