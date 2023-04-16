#include <GLFWMainWindows.h>
#include <logging/Logger.h>

auto main() -> int {
  Logger::Init();

  GLFWMainWindows::Init();

  GLFWMainWindows::MainLoop();

  GLFWMainWindows::Shutdown();

  Logger::Info("Goodbye from the ImDFD");
  return 0;
}
