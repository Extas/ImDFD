#include <ui/Menu.h>

Menu::Menu(std::string label) : m_Label(std::move(label)) {
}

void Menu::AddItem(
    const std::string &label, const std::function<void()> &callback) {
  m_Items.emplace_back(label, callback);
}

void Menu::Show() {
  if (ImGui::BeginMenu(m_Label.c_str())) {
    for (const auto &item : m_Items) {
      if (item.second != nullptr && ImGui::MenuItem(item.first.c_str())) {
        item.second();
      }
    }
    ImGui::EndMenu();
  }
}
