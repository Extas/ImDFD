#ifndef MAINMENUBAR_H
#define MAINMENUBAR_H

#include <BaseMenuBar.h>

#include <memory>

class MainMenuBar : public BaseMenuBar {
public:
  MainMenuBar();

private:
  void SetupFileMenu();
  void SetupEditMenu();
  void SetupViewMenu();
  void SetupHelpMenu();
};

#endif // MAINMENUBAR_H
