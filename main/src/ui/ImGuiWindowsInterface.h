#ifndef IMGUIWINDOWSINTERFACE_H
#define IMGUIWINDOWSINTERFACE_H

#include <imgui.h>

class ImGuiWindowsInterface {
private:
public:
  ImGuiWindowsInterface(const char *name = "ImGuiWindowsInterface");
  virtual ~ImGuiWindowsInterface() = default;

  virtual void Update() = 0;
  char *kMName;
};

ImGuiWindowsInterface::ImGuiWindowsInterface(const char *name) {
  kMName = new char[strlen(name) + 1];
  strcpy(kMName, name);
}

#endif // IMGUIWINDOWSINTERFACE_H
