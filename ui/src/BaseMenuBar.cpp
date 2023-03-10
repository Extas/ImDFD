#include <ui/BaseMenuBar.h>

auto BaseMenuBar::GetOrAddMenu(const std::string &label) -> Menu & {
  // Look for an existing menu with the specified label
  for (auto &menu : m_Menus) {
    if (menu.GetLabel() == label) {
      return menu;
    }
  }

  // If no existing menu found, create a new one and add it to the menu bar
  Menu menu(label);
  m_Menus.push_back(std::move(menu));
  return m_Menus.back();
}

void BaseMenuBar::AddMenuItem(
    const std::string &label, const std::function<void()> &callback) {
  if (m_Menus.empty()) {
    // If no menus exist, create a new one and add the item to it
    m_Menus.emplace_back("Menu");
  }
  m_Menus.back().AddItem(label, callback);
}

void BaseMenuBar::Show() {
  if (ImGui::BeginMainMenuBar()) {
    for (auto &menu : m_Menus) {
      menu.Show();
    }
    ImGui::EndMainMenuBar();
  }
}
