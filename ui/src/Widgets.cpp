#include <ui/Widgets.h>
void imdfd::ui::widgets::DrawTextWithLabel(
    const std::string &text, const std::string &label) {
  ImGui::Text(label.c_str());
  ImGui::SameLine();
  ImGui::Text(text.c_str());
}

void imdfd::ui::widgets::DrawInputText(
    std::string &str_ref, const std::string &label) {
  ImGui::Text(label.c_str());
  ImGui::SameLine();
  ImGui::InputText(("##" + label).c_str(), &str_ref);
}
