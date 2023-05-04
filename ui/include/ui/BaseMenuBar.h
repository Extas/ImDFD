#ifndef BASEMENUBAR_H
#define BASEMENUBAR_H
#define IMGUI_DEFINE_MATH_OPERATORS

#include <ui/Menu.h>

#include <functional>
#include <imgui.h>
#include <string>
#include <vector>

class BaseMenuBar {
public:
  BaseMenuBar() = default;

  // Get or add a menu to the menu bar
  auto GetOrAddMenu(const std::string &label) -> Menu &;

  // Add a new menu item to the last added menu
  void AddMenuItem(const std::string &label,
      const std::function<void()> &callback = nullptr);

  // DrawCustom the menu bar
  virtual void Show();

private:
  std::vector<Menu> m_Menus;
};

#endif // BASEMENUBAR_H
