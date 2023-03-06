#include <GLFWMainWindows.h>
#include <Logger.h>

int main() {
  Logger::Init();
  Logger::Trace("Welcome to the ImDFD");

  GLFWMainWindows::Init();

  GLFWMainWindows::MainLoop();

  GLFWMainWindows::Shutdown();

  Logger::Trace("Goodbye from the ImDFD");
  return 0;
}
