
#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_UTIL_WIDGETS_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_UTIL_WIDGETS_H_
#define IMGUI_DEFINE_MATH_OPERATORS

#include "drawing.h"
#include <imgui.h>

namespace ax {
namespace Widgets {

using Drawing::IconType;

void Icon(const ImVec2 &size, IconType type, bool filled,
    const ImVec4 &color = ImVec4(1, 1, 1, 1),
    const ImVec4 &innerColor = ImVec4(0, 0, 0, 0)) {
  if (ImGui::IsRectVisible(size)) {
    auto cursorPos = ImGui::GetCursorScreenPos();
    auto drawList = ImGui::GetWindowDrawList();
    ax::Drawing::DrawIcon(drawList, cursorPos, cursorPos + size, type, filled,
        ImColor(color), ImColor(innerColor));
  }

  ImGui::Dummy(size);
}

} // namespace Widgets
} // namespace ax
#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_UTIL_WIDGETS_H_
