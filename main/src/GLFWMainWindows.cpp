#include <GLFWMainWindows.h>

void GLFWMainWindows::Init(int width, int height, const char *title) {
  glfwSetErrorCallback(ErrorCallback);

  if (glfwInit() == 0) {
    throw std::runtime_error("Failed to initialize GLFW");
  }

  // Decide GL+GLSL versions
#if __APPLE__
  // GL 3.2 + GLSL 150
  glsl_version_ = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac
#else
  // GL 3.0 + GLSL 130
  glsl_version_ = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+
  // only glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 3.0+ only
#endif

  // Create window with graphics context
  window_ptr_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
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
    DearImGui::Update();
    DearImGui::Render();

    glfwSwapBuffers(window_ptr_);
  }

  DearImGui::Shutdown();
}

void GLFWMainWindows::Shutdown() {
  glfwDestroyWindow(window_ptr_);
  glfwTerminate();
}

void GLFWMainWindows::ErrorCallback(int error, const char *description) {
  fprintf(stderr, "Glfw Error %d: %s", error, description);
}
