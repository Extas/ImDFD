#include "imgui.h"
#include <cstdint>
#include <ui/Widgets.h>
#include <unordered_map>
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

void imdfd::ui::widgets::DrawListWithFilter(
    std::map<uint64_t, std::string> list,
    const std::function<void(uint64_t)>& callback) {
  static std::string filter;

  ImGui::Text("Filter:");
  ImGui::SameLine();
  ImGui::InputText("##Filter", &filter);

  ImGui::Separator();
  ImGui::Text("Items:");

  for (const auto &item : list) {
    if (filter.empty() || item.second.find(filter) != std::string::npos) {
      ImGui::PushID(item.first);
      ImGui::Text("%s", item.second.c_str());
      ImGui::SameLine();
      if (ImGui::Button("Select")) {
        if (callback) {
          callback(item.first);
        }
        ImGui::CloseCurrentPopup();
      }
      ImGui::PopID();
    }
  }
}

void imdfd::ui::widgets::DrawMenuItemList(std::map<uint64_t, std::string> list,
    const std::function<void(uint64_t)> &callback) {
  for (const auto &item : list) {
    if (ImGui::MenuItem(item.second.c_str())) {
	  if (callback) {
		callback(item.first);
	  }
	}
  }
}


auto imdfd::ui::widgets::DrawEditableInputTexts(std::vector<std::string> texts,
    std::uint64_t id) -> std::vector<std::string> {
  if (!texts.empty()) {
    auto hash_str = texts[0];
    auto hash = std::hash<std::string>{}(hash_str);
    id = id + hash;
  }
  static std::unordered_map<std::uint64_t, bool> editing;
  auto &edit_mode = editing[id];

  static std::vector<std::string> edited_texts;
  edited_texts.clear();

  ImGui::BeginGroup();

  if (edit_mode) {
    edited_texts = texts;
    for (size_t i = 0; i < edited_texts.size(); ++i) {
      ImGui::InputText(("##" + std::to_string(id) + std::to_string(i)).c_str(),
          &edited_texts[i]);
      if (i < edited_texts.size() - 1) {
        ImGui::SameLine();
      }
    }
    ImGui::BeginGroup();
    if (ImGui::Button("OK")) {
      texts = edited_texts;
      edit_mode = false;
    }
    ImGui::SameLine();
    if (ImGui::Button("Cancel")) {
      edit_mode = false;
    }
    ImGui::EndGroup();
  } else {
    for (const auto &kText : texts) {
      ImGui::TextUnformatted(kText.c_str());
      ImGui::SameLine();
    }
    auto edit_name = "Edit" + std::to_string(id);
    if (ImGui::Button(edit_name.c_str())) {
      edit_mode = true;
    }
  }

  ImGui::EndGroup();

  return edited_texts;
}
