#ifndef IMDFD_UI_INCLUDE_UI_WIDGETS_H_
#define IMDFD_UI_INCLUDE_UI_WIDGETS_H_

#include "BasePopup.h"
#include <cstring>
#include <functional>
#include <imgui.h>
#include <imgui_stdlib.h>
#include <map>
#include <string>
#include <vector>

namespace imdfd::ui::widgets {

void DrawTextWithLabel(const std::string &text, const std::string &label);

void DrawInputText(std::string &str_ref, const std::string &label);

void DrawListWithFilter(std::map<uint64_t, std::string> list, const std::function<void(uint64_t)>& callback);

auto DrawEditableInputTexts(std::vector<std::string> texts, std::uint64_t id)
    -> std::vector<std::string>;

class ListWithFilterPopup : public BasePopup {
public:
  ListWithFilterPopup(std::string title,
      std::map<uint64_t, std::string> list,
      const std::function<void(uint64_t)>& callback)
      : BasePopup(std::move(title)), list_(std::move(list)), callback_(callback) {}

  void DrawContents() override {
    imdfd::ui::widgets::DrawListWithFilter(list_, callback_);
  }

private:
  std::map<uint64_t, std::string> list_;
  std::function<void(uint64_t)> callback_;
};


} // namespace imdfd::ui::widgets

#endif // IMDFD_UI_INCLUDE_UI_WIDGETS_H_
