#include <GLFWMainWindows.h>

int main() {

  GLFWMainWindows::Init();

  GLFWMainWindows::MainLoop();

  GLFWMainWindows::Shutdown();

  return 0;
}
