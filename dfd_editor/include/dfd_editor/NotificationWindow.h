#ifndef IMNOTIFICATION_H
#define IMNOTIFICATION_H

#include "spdlog/common.h"
#include <imgui.h>
#include <ui/BaseWindow.h>

#include <chrono>
#include <mutex>
#include <spdlog/sinks/base_sink.h>
#include <string>
#include <vector>

// Usage:
//  static ExampleAppLog my_log;
//  my_log.AddLog("Hello %d world\n", 123);
//  my_log.DrawCustom("title");
struct ExampleAppLog {
  ImGuiTextBuffer buf;
  ImGuiTextFilter filter;
  ImVector<int> line_offsets; // Index to lines offset. We maintain this with
                              // AddLog() calls.
  bool auto_scroll{true};     // Keep scrolling if already at the bottom.

  ExampleAppLog() {
    Clear();
  }

  void Clear() {
    buf.clear();
    line_offsets.clear();
    line_offsets.push_back(0);
  }

  template <typename... Args> void AddLog(const char *fmt, Args... args) {
    int old_size = buf.size();
    std::string formatted_string = FormatString(fmt, args...);
    buf.append(formatted_string.c_str());

    for (int new_size = buf.size(); old_size < new_size; old_size++) {
      if (buf[old_size] == '\n') {
        line_offsets.push_back(old_size + 1);
      }
    }
  }

  template <typename... Args>
  auto FormatString(const char *fmt, Args... args) -> std::string {
    size_t buf_size = std::snprintf(nullptr, 0, fmt, args...) + 1;
    std::vector<char> buffer(buf_size);
    std::snprintf(buffer.data(), buf_size, fmt, args...);
    return std::string(buffer.data(), buffer.size() - 1);
  }

  void Draw(const char *title, bool *p_open = nullptr) {
    if (!ImGui::Begin(title, p_open)) {
      ImGui::End();
      return;
    }

    // Options menu
    if (ImGui::BeginPopup("Options")) {
      ImGui::Checkbox("Auto-scroll", &auto_scroll);
      ImGui::EndPopup();
    }

    // Main window
    if (ImGui::Button("Options")) {
      ImGui::OpenPopup("Options");
    }
    ImGui::SameLine();
    bool clear = ImGui::Button("Clear");
    ImGui::SameLine();
    bool copy = ImGui::Button("Copy");
    ImGui::SameLine();
    filter.Draw("Filter", -100.0f);

    ImGui::Separator();

    if (ImGui::BeginChild("scrolling", ImVec2(0, 0), false,
            ImGuiWindowFlags_HorizontalScrollbar)) {
      if (clear) {
        Clear();
      }
      if (copy) {
        ImGui::LogToClipboard();
      }

      ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
      const char *buf_begin = buf.begin();
      const char *buf_end = buf.end();
      if (filter.IsActive()) {
        // In this example we don't use the clipper when Filter is enabled.
        // This is because we don't have random access to the result of our
        // filter. A real application processing logs with ten of thousands of
        // entries may want to store the result of search/filter.. especially if
        // the filtering function is not trivial (e.g. reg-exp).
        for (int line_no = 0; line_no < line_offsets.Size; line_no++) {
          const char *line_start = buf_begin + line_offsets[line_no];
          const char *line_end =
              (line_no + 1 < line_offsets.Size)
                  ? (buf_begin + line_offsets[line_no + 1] - 1)
                  : buf_end;
          if (filter.PassFilter(line_start, line_end)) {
            ImGui::TextUnformatted(line_start, line_end);
          }
        }
      } else {
        // The simplest and easy way to display the entire buffer:
        //   ImGui::TextUnformatted(buf_begin, buf_end);
        // And it'll just work. TextUnformatted() has specialization for large
        // blob of text and will fast-forward to skip non-visible lines. Here we
        // instead demonstrate using the clipper to only process lines that are
        // within the visible area.
        // If you have tens of thousands of items and their processing cost is
        // non-negligible, coarse clipping them on your side is recommended.
        // Using ImGuiListClipper requires
        // - A) random access into your data
        // - B) items all being the  same height,
        // both of which we can handle since we have an array pointing to the
        // beginning of each line of text. When using the filter (in the block
        // of code above) we don't have random access into the data to display
        // anymore, which is why we don't use the clipper. Storing or skimming
        // through the search result would make it possible (and would be
        // recommended if you want to search through tens of thousands of
        // entries).
        ImGuiListClipper clipper;
        clipper.Begin(line_offsets.Size);
        while (clipper.Step()) {
          for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd;
               line_no++) {
            const char *line_start = buf_begin + line_offsets[line_no];
            const char *line_end =
                (line_no + 1 < line_offsets.Size)
                    ? (buf_begin + line_offsets[line_no + 1] - 1)
                    : buf_end;
            ImGui::TextUnformatted(line_start, line_end);
          }
        }
        clipper.End();
      }
      ImGui::PopStyleVar();

      // Keep up at the bottom of the scroll region if we were already at the
      // bottom at the beginning of the frame. Using a scrollbar or mouse-wheel
      // will take away from the bottom edge.
      if (auto_scroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
        ImGui::SetScrollHereY(1.0F);
      }
    }
    ImGui::EndChild();
    ImGui::End();
  }
};

class NotificationWindow : public BaseWindow {
public:
  NotificationWindow();

  static void AddNotification(const std::string &message);

  void DrawContents() override;

private:
  inline static ExampleAppLog log_;
  spdlog::sink_ptr sink_;
};

class NotificationWindowSink : public spdlog::sinks::base_sink<std::mutex> {
public:
  explicit NotificationWindowSink(NotificationWindow *window)
      : window_(window) {
  }

protected:
  void sink_it_(const spdlog::details::log_msg &msg) override;

  void flush_() override {
  }

private:
  NotificationWindow *window_;
};

#endif
