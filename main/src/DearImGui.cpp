#include <DearImGui.h>
#include <GLFW/glfw3.h>
#include <imgui_node_editor.h>
#include <string_view>

namespace ed = ax::NodeEditor;
auto const kMContext = ed::CreateEditor();

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

  // begin
  ImGui::Begin("Node Editor");
  ed::SetCurrentEditor(kMContext);
  ed::Begin("My Editor", ImVec2(0.0, 0.0f));
  int uniqueId = 1;
  // Start drawing nodes.
  ed::BeginNode(uniqueId++);
  ImGui::Text("Node A");
  ed::BeginPin(uniqueId++, ed::PinKind::Input);
  ImGui::Text("-> In");
  ed::EndPin();
  ImGui::SameLine();
  ed::BeginPin(uniqueId++, ed::PinKind::Output);
  ImGui::Text("Out ->");
  ed::EndPin();
  ed::EndNode();
  ed::End();
  ed::SetCurrentEditor(nullptr);
  ImGui::End();
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
  ed::DestroyEditor(kMContext);

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
