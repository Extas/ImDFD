
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAPROCESS_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAPROCESS_H_

#include "DfdNode.h"
class Dfd;

class DataProcess : public DfdNode {
public:
  DataProcess(const std::string &name, std::pair<float, float> pos);
  DataProcess(uint64_t id, const std::string &name, std::pair<float, float> pos);
  std::string process_description_;
  std::shared_ptr<Dfd> sub_dfd_;

  [[nodiscard]] auto Serialize() const -> std::string override;
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAPROCESS_H_
