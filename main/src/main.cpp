#include <GLFWMainWindows.h>
#include <logging/Logger.h>

int main() {
  Logger::Init();

  GLFWMainWindows::Init();

  GLFWMainWindows::MainLoop();

  GLFWMainWindows::Shutdown();

  Logger::Info("Goodbye from the ImDFD");
  return 0;
}
