#include <GLFWMainWindows.h>
#include <Logger.h>

int main() {
  Logger::Init();
  Logger::Info("Welcome to the ImDFD");

  GLFWMainWindows::Init();

  GLFWMainWindows::MainLoop();

  GLFWMainWindows::Shutdown();

  Logger::Info("Goodbye from the ImDFD");
  return 0;
}
