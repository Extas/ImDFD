#ifndef IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_INFOWINDOW_H_
#define IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_INFOWINDOW_H_

#include <dfd_model/DataFlow.h>
#include <dfd_model/Dfd.h>
#include <dfd_model/DfdNode.h>
#include <imgui.h>
#include <signal/SignalHandel.h>
#include <ui/BaseWindow.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

class Info {
public:
  Info() = default;

  void LoadNode(const std::shared_ptr<DfdNode> &node) {
    if (node) {
      name_ = node->name_;
      description_ = node->description_;
    }
  }

  void LoadLink(const std::shared_ptr<DataFlow> &link) {
    if (link) {
      name_ = link->name_;
      description_ = link->description_;
    }
  }

  std::string name_;
  std::string description_;
};

class InfoWindow : public BaseWindow {
public:
  explicit InfoWindow() : BaseWindow("Info") {
    SignalHandel::Instance().selected_node_.connect([this](int64_t node_id) {
      auto node = dfd_->GetNodeById(node_id);
      if (node) {
        info_.LoadNode(node);
      }
    });

    SignalHandel::Instance().selected_link_.connect([this](int64_t link_id) {
      auto link = dfd_->GetFlowById(link_id);
      if (link) {
        info_.LoadLink(link);
      }
    });
  }

  void DrawContents() override {
    ImGui::Text("%s", info_.name_.c_str());
    ImGui::Text("%s", info_.description_.c_str());
  }

  void LoadDfd(const std::shared_ptr<Dfd> &dfd) {
    dfd_ = dfd;
  }

private:
  std::shared_ptr<Dfd> dfd_;
  Info info_;
};

#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_INFOWINDOW_H_
