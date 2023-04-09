#ifndef IMDFD__DEARIMGUI_H_
#define IMDFD__DEARIMGUI_H_

#include <GLFW/glfw3.h>
#include <dfd_editor/DfdManager.h>
#include <ui/BaseWindow.h>
#include <ui/MainMenuBar.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <memory>
#include <vector>

class DearImGui {
public:
  static void Init(GLFWwindow *window, const char *glsl_version);
  static void NewFrame();
  static void Draw();
  static void Render();
  static void Shutdown();

private:
  inline static ImGuiContext *context_ = nullptr;
  static void IoConfig();

  inline static std::vector<std::shared_ptr<BaseWindow>> windows_;
  static void AddWindow(std::shared_ptr<BaseWindow> window);

  inline static MainMenuBar menu_bar_;
  inline static DfdManager dfd_manager_;
};

#endif // IMDFD__DEARIMGUI_H_
