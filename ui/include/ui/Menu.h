#ifndef MENU_H
#define MENU_H

#include <functional>
#include <imgui.h>
#include <string>
#include <vector>

class Menu {
public:
  explicit Menu(std::string label);
  ~Menu() = default;

  // Add a new menu item to this menu
  void AddItem(const std::string &label,
      const std::function<void()> &callback = nullptr);

  // Draw this menu and its items
  void Show();

  // Get the label of this menu
  [[nodiscard]] auto GetLabel() const -> const std::string & {
    return m_Label;
  }

private:
  std::string m_Label;
  std::vector<std::pair<std::string, std::function<void()>>> m_Items;

public:
  Menu(Menu &&) = default;
  Menu(const Menu &) = delete;
  auto operator=(Menu &&) -> Menu & = delete;
  auto operator=(const Menu &) -> Menu & = delete;
};

#endif // MENU_H
