#ifndef IMDFD_UI_INCLUDE_UI_WIDGETS_H_
#define IMDFD_UI_INCLUDE_UI_WIDGETS_H_

#include <cstring>
#include <imgui.h>
#include <imgui_stdlib.h>
#include <string>
#include <vector>

namespace imdfd::ui::widgets {

void DrawTextWithLabel(const std::string &text, const std::string &label);

void DrawInputText(std::string &str_ref, const std::string &label);

auto DrawEditableInputTexts(std::vector<std::string> texts, std::uint64_t id)
    -> std::vector<std::string>;

} // namespace imdfd::ui::widgets

#endif // IMDFD_UI_INCLUDE_UI_WIDGETS_H_
