#include <GLFWMainWindows.h>
#include <application/application.h>
#include <logging/Logger.h>

int main() {
  Logger::Init();
  Logger::Info("Welcome to the ImDFD");

  Application app("ImDFD");

  if (app.Create()) {
    app.Run();
  }

  GLFWMainWindows::Init();

  GLFWMainWindows::MainLoop();

  GLFWMainWindows::Shutdown();

  Logger::Info("Goodbye from the ImDFD");
  return 0;
}
