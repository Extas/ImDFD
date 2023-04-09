
#ifndef IMDFD_DFD_EDITOR_SIGNAL_INCLUDE_SIGNAL_SIGNALHANDEL_H_
#define IMDFD_DFD_EDITOR_SIGNAL_INCLUDE_SIGNAL_SIGNALHANDEL_H_

#include <sigslot/signal.hpp>
#include <cstdint>

class Dfd;

class SignalHandel {
public:
  static auto Instance() -> SignalHandel & {
    static SignalHandel instance;
    return instance;
  }

  SignalHandel(const SignalHandel &) = delete;
  auto operator=(const SignalHandel &) -> SignalHandel & = delete;

  sigslot::signal<int64_t> navigate_sub_diagram_onclick_;
  sigslot::signal<const std::shared_ptr<Dfd> &> create_new_dfd_;
  sigslot::signal<int64_t, const std::string &, std::pair<float, float>>
      create_new_node_;

  sigslot::signal<> menu_new_click_;
  sigslot::signal<const std::string &> menu_open_click_;
  sigslot::signal<> menu_save_click_;
  sigslot::signal<const std::string &> menu_saveas_click_;

  sigslot::signal<uint64_t> selected_node_;
  sigslot::signal<uint64_t> selected_link_;

private:
  SignalHandel() = default;
};
#endif // IMDFD_DFD_EDITOR_SIGNAL_INCLUDE_SIGNAL_SIGNALHANDEL_H_
