
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_EXTERNALENTITY_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_EXTERNALENTITY_H_

#include "DfdNode.h"

class ExternalEntity : public DfdNode {
public:
  static auto Create(std::string name, std::pair<float, float> pos)
      -> std::shared_ptr<ExternalEntity>;
  static auto Create(uint64_t id, std::string name, std::pair<float, float> pos)
      -> std::shared_ptr<ExternalEntity>;

  [[nodiscard]] auto Serialize() const -> nlohmann::json override {
    return DfdNode::Serialize("ExternalEntity");
  }
  [[nodiscard]] static auto DeSerialize(nlohmann::json json)
      -> std::shared_ptr<ExternalEntity>;

private:
  ExternalEntity(std::string name, std::pair<float, float> pos);
  ExternalEntity(uint64_t id, std::string name, std::pair<float, float> pos);
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_EXTERNALENTITY_H_
