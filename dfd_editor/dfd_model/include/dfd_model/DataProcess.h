
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAPROCESS_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAPROCESS_H_

#include "DfdNode.h"
class Dfd;

class DataProcess : public DfdNode {
public:
  static auto Create(const std::string &name, std::pair<float, float> pos)
      -> std::shared_ptr<DataProcess>;

  static auto Create(uint64_t id, const std::string &name,
      std::pair<float, float> pos) -> std::shared_ptr<DataProcess>;

  std::string process_description_;
  std::shared_ptr<Dfd> sub_dfd_;

  [[nodiscard]] auto Serialize() const -> std::string override;

private:
  DataProcess(const std::string &name, std::pair<float, float> pos);
  DataProcess(
      uint64_t id, const std::string &name, std::pair<float, float> pos);
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAPROCESS_H_
