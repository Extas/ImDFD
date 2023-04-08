#include <DearImGui.h>
#include <logging/Logger.h>

#include <dfd_editor/InfoWindow.h>
#include <dfd_editor/MultCanvasWindow.h>
#include <dfd_editor/NotificationWindow.h>
#include <dfd_model/Dfd.h>
#include <filesystem>
#include <fstream>
#include <memory>
#include <ui/BaseWindow.h>

void DearImGui::Init(GLFWwindow *window, const char *glsl_version) {
  Logger::Trace("Initializing Dear ImGui");
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  IoConfig();

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
  ImGui::StyleColorsDark();

  AddWindow(std::make_shared<BaseWindow>("test"));
  AddWindow(std::make_shared<NotificationWindow>());
  Logger::Info("Welcome to the ImDFD");

  auto mult_canvas_window =
      std::make_shared<MultCanvasWindow>("Node Editor Window");
  AddWindow(mult_canvas_window);

  auto info_window = std::make_shared<InfoWindow>();
  AddWindow(info_window);

  auto test_dfd = std::make_shared<Dfd>("test_dfd");
  test_dfd->CreateTestData();

  auto test_seri = test_dfd->Serialize();
  auto test_dfd2 = Dfd::DeSerialize(test_seri);

  mult_canvas_window->LoadDfd(test_dfd2);
  info_window->LoadDfd(test_dfd2);
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
    auto test_file = OpenTextFile(menu_bar_.GetFileDialog().GetSelected());
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
  const auto kFontsDir =
      std::filesystem::current_path().parent_path() / "data" / "fonts";
  if (std::filesystem::exists(kFontsDir)) {
    for (const auto &kFontPath :
        std::filesystem::directory_iterator(kFontsDir)) {
      if (kFontPath.path().extension() == ".ttf") {
        imgui_io.Fonts->AddFontFromFileTTF(kFontPath.path().string().data(),
            kFontSize, nullptr, imgui_io.Fonts->GetGlyphRangesChineseFull());
        break;
      }
    }
  }
}

void DearImGui::AddWindow(std::shared_ptr<BaseWindow> window) {
  windows_.push_back(std::move(window));
}

auto DearImGui::OpenTextFile(const std::filesystem::path &filepath)
    -> std::string {
  std::string ret = "Error opening file!";

  std::ifstream file(filepath);
  if (file.is_open()) {
    std::string content((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
    file.close();
    return content;
  }

  return ret;
}
