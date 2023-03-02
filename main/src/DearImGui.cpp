#include <DearImGui.h>
#include <string_view>

#include <ui/NodeEditerDemo.hpp>

void DearImGui::Init(GLFWwindow *window, const char *glsl_version) {
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

void DearImGui::Update() {

  ImGui::ShowDemoWindow();

  const std::string_view kTestText = "font test";
  ImGui::DebugTextEncoding(kTestText.data());

  static NodeEditerDemo node_editer_demo;
  node_editer_demo.Update();
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
  //  imgui_io.ConfigFlags |= ImGuiViewportFlags_NoDecoration;
  imgui_io.ConfigFlags |= ImGuiCol_DockingEmptyBg;

  //   font
  constexpr float kFontSize = 26.0F;
  const std::string_view kFontPath =
      "../../../../resources/fonts/sarasa-mono-sc-nerd-regular.ttf";
  imgui_io.Fonts->AddFontFromFileTTF(kFontPath.data(), kFontSize, nullptr,
      imgui_io.Fonts->GetGlyphRangesChineseFull());
}