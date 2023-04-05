
#ifndef IMDFD_DFD_EDITOR_SIGNAL_INCLUDE_SIGNAL_SIGNALHANDEL_H_
#define IMDFD_DFD_EDITOR_SIGNAL_INCLUDE_SIGNAL_SIGNALHANDEL_H_

#include <sigslot/signal.hpp>

class Dfd;

class SignalHandel {
public:
  static auto Instance() -> SignalHandel & {
    static SignalHandel instance;
    return instance;
  }

  SignalHandel(const SignalHandel &) = delete;
  auto operator=(const SignalHandel &) -> SignalHandel & = delete;

  sigslot::signal<int, const std::string &> processing_content_changed_;
  sigslot::signal<int> navigate_sub_diagram_onclick_;
  sigslot::signal<const std::shared_ptr<Dfd> &, int64_t &> create_new_dfd_;
  sigslot::signal<const std::string &, std::pair<float, float>>
      create_new_node_;

private:
  SignalHandel() = default;
};
#endif // IMDFD_DFD_EDITOR_SIGNAL_INCLUDE_SIGNAL_SIGNALHANDEL_H_
