
#ifndef IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_DFDMANAGER_H_
#define IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_DFDMANAGER_H_

#include <dfd_model/Dfd.h>
#include <signal/SignalHandel.h>

class DfdManager {
public:
  DfdManager();
  using DfdLoadedCallback = std::function<void(const std::shared_ptr<Dfd> &)>;

  void AddDfdLoadedCallback(const DfdLoadedCallback &callback) {
    dfd_loaded_callbacks_ = callback;
  }

  void NewDfd();
  void OpenDfdFormFile(const std::filesystem::path &filepath);
  static void SaveAsDfdToFile(
      const std::filesystem::path &filepath, const std::shared_ptr<Dfd> &dfd);
  static void SaveDfd();

private:
  inline static std::shared_ptr<Dfd> current_dfd_;
  inline static std::filesystem::path current_dfd_path_;
  DfdLoadedCallback dfd_loaded_callbacks_;
};

#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_DFDMANAGER_H_
