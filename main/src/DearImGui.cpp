#include <DearImGui.h>
#include <Logger.h>

#include <BaseWindow.h>
#include <InfoWindow.h>
#include <MainMenuBar.h>

#include <filesystem>
#include <memory>
#include <string_view>

void DearImGui::Init(GLFWwindow *window, const char *glsl_version) {
  Logger::Trace("Initializing Dear ImGui");
  IMGUI_CHECKVERSION();
  context_ = ImGui::CreateContext();

  IoConfig();

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
  ImGui::StyleColorsDark();
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

  const std::string_view kTestText = "font test";
  ImGui::DebugTextEncoding(kTestText.data());

  BaseWindow window("test window");
  window.Show();
  MainMenuBar menu_bar;
  menu_bar.Show();
  auto info = ElementInfo("test", "test");
  auto info_window = InfoWindow(info);
  info_window.DrawContents();
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
