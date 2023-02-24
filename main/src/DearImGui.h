#ifndef IMDFD__DEARIMGUI_H_
#define IMDFD__DEARIMGUI_H_

#include <GLFW/glfw3.h>
#include <memory>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

class DearImGui {
public:
  static void Init(GLFWwindow *window, const char *glsl_version);
  static void NewFrame();
  static void Update();
  static void Render();
  static void Shutdown();

private:
  inline static ImGuiContext *context_ = nullptr;
  static void IoConfig();

  // Container for storing imgui window classes
  // std::vector<std::unique_ptr<ImGuiWindow>> windows_;
};

#endif // IMDFD__DEARIMGUI_H_
