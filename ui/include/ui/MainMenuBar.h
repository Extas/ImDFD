#ifndef MAINMENUBAR_H
#define MAINMENUBAR_H

#include <imgui.h>

#include <imfilebrowser.h>
#include <ui/BaseMenuBar.h>

#include <memory>

class MainMenuBar : public BaseMenuBar {
public:
  MainMenuBar();

  void Show() override;

  auto GetFileDialog() -> ImGui::FileBrowser &;

private:
  void SetupFileMenu();
  void SetupEditMenu();
  void SetupViewMenu();
  void SetupHelpMenu();

  ImGui::FileBrowser file_dialog_;
};

#endif // MAINMENUBAR_H
