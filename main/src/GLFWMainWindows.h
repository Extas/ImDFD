#ifndef IMDFD__WINDOWS_H_
#define IMDFD__WINDOWS_H_

#include <DearImGui.h>
#include <glad/glad.h>
#include <stdexcept>

#include <GLFW/glfw3.h>

constexpr int kWidth = 1920;
constexpr int kHeight = 1080;
constexpr char kTitle[] = "Dear ImGui - ImDFD";

class GLFWMainWindows {
public:
  static void Init(
      int width = kWidth, int height = kHeight, const char *title = kTitle);
  static void MainLoop();
  static void Shutdown();
  static void ErrorCallback(int error, const char *description);

private:
  static inline GLFWwindow *window_ptr_ = nullptr;
  static const inline char *glsl_version_ = "#version 130";
};

#endif // IMDFD__WINDOWS_H_
