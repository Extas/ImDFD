#include <GLFWMainWindows.h>
#include <logging/Logger.h>

#include <stdexcept>
#include <string>

void GLFWMainWindows::Init(int width, int height, const std::string &title) {
  Logger::Trace("Initializing GLFW");
  std::string info = "Window size: " + std::to_string(width) + "x" +
                     std::to_string(height) + ", title: " + title;
  Logger::Info(info.c_str());

  glfwWindowHint(GLFW_VISIBLE, 0);
  glfwWindowHint(GLFW_SCALE_TO_MONITOR, GL_TRUE);
  glfwSetErrorCallback(ErrorCallback);

  if (glfwInit() == 0) {
    Logger::Error("Failed to initialize GLFW");
    exit(EXIT_FAILURE);
  }

  // Decide GL+GLSL versions
#if __APPLE__
  // GL 3.2 + GLSL 150
  glsl_version_ = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac
#else
  // GL 3.0 + GLSL 130
  glsl_version_ = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // 3.0+ only
#endif

  // Create window with graphics context
  window_ptr_ =
      glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (window_ptr_ == nullptr) {
    throw std::runtime_error("Failed to create GLFW window");
  }

  glfwMakeContextCurrent(window_ptr_);

  glfwSwapInterval(1); // Enable vsync

  if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) ==
      0) { // tie window context to glad's opengl funcs
    throw std::runtime_error("Failed to initialize OpenGL context");
  }

  int screen_width = 0;
  int screen_height = 0;
  glfwGetFramebufferSize(window_ptr_, &screen_width, &screen_height);
  glViewport(0, 0, screen_width, screen_height);
}

void GLFWMainWindows::MainLoop() {

  DearImGui::Init(window_ptr_, glsl_version_);

  while (glfwWindowShouldClose(window_ptr_) == 0) {
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT);

    DearImGui::NewFrame();
    DearImGui::Draw();
    DearImGui::Render();

    glfwSwapBuffers(window_ptr_);
  }

  DearImGui::Shutdown();
}

void GLFWMainWindows::Shutdown() {
  Logger::Trace("Shutting down GLFW");
  glfwDestroyWindow(window_ptr_);
  glfwTerminate();
}

void GLFWMainWindows::ErrorCallback(int error, const char *description) {
  std::string error_msg =
      "GLFW Error: " + std::to_string(error) + " - " + std::string(description);
  Logger::Error(error_msg.c_str());
}
