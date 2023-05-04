#ifndef MAINMENUBAR_H
#define MAINMENUBAR_H
#define IMGUI_DEFINE_MATH_OPERATORS

#include <imgui.h>

#include <imfilebrowser.h>
#include <ui/BaseMenuBar.h>

#include <memory>

class MainMenuBar : public BaseMenuBar {
public:
  MainMenuBar();

  void Show() override;

private:
  void SetupFileMenu();
  void SetupEditMenu();
  void SetupViewMenu();
  void SetupHelpMenu();

  ImGui::FileBrowser file_dialog_;
  int file_operate_type_ = 0;
};

#endif // MAINMENUBAR_H
