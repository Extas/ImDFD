#ifndef GLFWMAINWINDOWS_H
#define GLFWMAINWINDOWS_H

#include <glad/glad.h>

#include <DearImGui.h>
#include <string>

#include <GLFW/glfw3.h>

constexpr int kWidth = 1920;
constexpr int kHeight = 1080;
const std::string kTitle = "Dear ImGui - ImDFD";

class GLFWMainWindows {
public:
  static void Init(int width = kWidth, int height = kHeight,
      const std::string &title = kTitle);
  static void MainLoop();
  static void Shutdown();
  static void ErrorCallback(int error, const char *description);

private:
  static inline GLFWwindow *window_ptr_ = nullptr;
  static const inline char *glsl_version_ = "#version 130";
};

#endif // GLFWMAINWINDOWS_H
