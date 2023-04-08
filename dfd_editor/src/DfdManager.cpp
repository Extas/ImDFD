#include <dfd_editor/DfdManager.h>
#include <fstream>

DfdManager::DfdManager() {
  SignalHandel::Instance().menu_open_click_.connect(
      [this](const std::string &filepath) { OpenDfdFormFile(filepath); });

  SignalHandel::Instance().menu_saveas_click_.connect(
      [this](const std::string &filepath) {
        SaveAsDfdToFile(filepath, current_dfd_);
      });

  SignalHandel::Instance().menu_new_click_.connect([this]() { NewDfd(); });

  SignalHandel::Instance().menu_save_click_.connect([]() { SaveDfd(); });
}

void DfdManager::OpenDfdFormFile(const std::filesystem::path &filepath) {
  current_dfd_path_ = filepath;

  std::ifstream file(current_dfd_path_);
  if (file.is_open()) {
    std::string content((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
    file.close();

    auto loaded_dfd = Dfd::DeSerialize(content);
    current_dfd_ = loaded_dfd;

    dfd_loaded_callbacks_(current_dfd_);
  }
}

void DfdManager::SaveAsDfdToFile(
    const std::filesystem::path &filepath, const std::shared_ptr<Dfd> &dfd) {
  current_dfd_path_ = filepath;

  std::ofstream file(current_dfd_path_);
  if (file.is_open()) {
    file << dfd->GetJsonString();

    file.close();
  }
}

void DfdManager::NewDfd() {
  current_dfd_ = std::make_shared<Dfd>("example");
  current_dfd_->CreateExampleData();
  dfd_loaded_callbacks_(current_dfd_);
}

void DfdManager::SaveDfd() {
  if (current_dfd_path_.empty()) {
    return;
  }

  std::ofstream file(current_dfd_path_);
  if (file.is_open()) {
    file << current_dfd_->GetJsonString();

    file.close();
  }
}
