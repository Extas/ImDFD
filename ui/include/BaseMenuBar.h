#ifndef BASEMENUBAR_H
#define BASEMENUBAR_H

#include <Menu.h>

#include <functional>
#include <imgui.h>
#include <string>
#include <vector>

class BaseMenuBar {
public:
  BaseMenuBar();

  // Get or add a menu to the menu bar
  Menu &GetOrAddMenu(const std::string &label);

  // Add a new menu item to the last added menu
  void AddMenuItem(const std::string &label,
      const std::function<void()> &callback = nullptr);

  // Show the menu bar
  void Show();

private:
  std::vector<Menu> m_Menus;
};

#endif // BASEMENUBAR_H
