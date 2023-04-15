#include "imgui.h"
#include <string>
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
    const std::function<void(uint64_t)> &callback) {
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

void imdfd::ui::widgets::DrawEditableInputTexts(
    const std::vector<std::reference_wrapper<std::string>> &texts) {
  auto size = texts.size();
  static std::unordered_map<void *, bool> editing;

  ImGui::BeginGroup();

  static size_t i = 0;
  for (auto &text_ref : texts) {
    auto edit_mode = editing[&text_ref.get()];

    ImGui::PushID(i);
    if (edit_mode) {
      if (ImGui::Button("OK")) {
        editing[&text_ref.get()] = false;
      }
    } else {
      if (ImGui::Button("Edit##")) {
        editing[&text_ref.get()] = true;
      }
    }

    ImGui::SameLine();
    std::string &text = text_ref.get();
    if (edit_mode) {
      ImGui::InputText("##", &text);
      if (i < texts.size() - 1) {
        ImGui::SameLine();
      }
    } else {
      ImGui::TextUnformatted(text.c_str());
      if (i < texts.size() - 1) {
        ImGui::SameLine();
      }
    }
    ++i;
    if (i == size) {
      i = 0;
    }
    ImGui::PopID();
  }

  ImGui::EndGroup();
}

void imdfd::ui::widgets::DrawCustomTable(
    const std::vector<std::string> &columnNames,
    const std::vector<std::vector<std::reference_wrapper<std::string>>>
        &rowData,
    const std::map<std::string, std::function<void(int)>> &action_callbacks) {
  int numColumns = columnNames.size();

  // Table setup
  ImGui::BeginTable("custom_table", numColumns + 1,
      ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg);

  // Set up columns
  for (const auto &columnName : columnNames) {
    ImGui::TableSetupColumn(columnName.c_str());
  }
  ImGui::TableSetupColumn("Action");
  ImGui::TableHeadersRow();

  // Inserting data into the table
  int rowIndex = 0;
  for (const auto &row : rowData) {
    ImGui::TableNextRow();

    for (int colIndex = 0; colIndex < numColumns; ++colIndex) {
      ImGui::TableSetColumnIndex(colIndex);
      // gen unique id by rowIndex and colIndex
      auto id = rowIndex * numColumns + colIndex;
      ImGui::PushID(id);
      DrawEditableInputTexts({row[colIndex]});
      ImGui::PopID();
    }

    // Action column
    ImGui::TableSetColumnIndex(numColumns);
    int buttonIndex = 0;
    for (const auto &[buttonName, callback] : action_callbacks) {
      if (ImGui::Button(
              (buttonName + "##" + std::to_string(rowIndex)).c_str())) {
        callback(rowIndex);
      }
      if (buttonIndex < static_cast<int>(action_callbacks.size()) - 1) {
        ImGui::SameLine();
      }
      ++buttonIndex;
    }

    ++rowIndex;
  }

  ImGui::EndTable();
}
