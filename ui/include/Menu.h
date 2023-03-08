#ifndef MENU_H
#define MENU_H

#include <functional>
#include <imgui.h>
#include <string>
#include <vector>

class Menu {
public:
  Menu(const std::string &label);
  ~Menu() = default;

  // Add a new menu item to this menu
  void AddItem(const std::string &label,
      const std::function<void()> &callback = nullptr);

  // Show this menu and its items
  void Show();

  // Get the label of this menu
  const std::string &GetLabel() const {
    return m_Label;
  }

private:
  std::string m_Label;
  std::vector<std::pair<std::string, std::function<void()>>> m_Items;
};

#endif // MENU_H
