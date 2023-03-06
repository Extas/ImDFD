#include <GLFWMainWindows.h>
#include <logger.h>

int main() {
  Logger::Init();
  Logger::Trace("Hello World!");

  GLFWMainWindows::Init();

  GLFWMainWindows::MainLoop();

  GLFWMainWindows::Shutdown();

  return 0;
}
