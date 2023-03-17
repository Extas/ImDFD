
#ifndef IMDFD_DFD_EDITOR_SIGNAL_INCLUDE_SIGNAL_SIGNALHANDEL_H_
#define IMDFD_DFD_EDITOR_SIGNAL_INCLUDE_SIGNAL_SIGNALHANDEL_H_

#include <sigslot/signal.hpp>

class SignalHandel {
public:
  // 获取SignalManager实例
  static auto Instance() -> SignalHandel & {
    static SignalHandel instance;
    return instance;
  }

  // 禁止复制和赋值
  SignalHandel(const SignalHandel &) = delete;
  auto operator=(const SignalHandel &) -> SignalHandel & = delete;

  sigslot::signal<int, const std::string &> processing_content_changed_;
  sigslot::signal<int> navigate_sub_diagram_onclick_;
  sigslot::signal<const std::string &, int &> create_new_canvas_;

private:
  SignalHandel() = default;
};
#endif // IMDFD_DFD_EDITOR_SIGNAL_INCLUDE_SIGNAL_SIGNALHANDEL_H_
