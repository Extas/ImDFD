
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_EXTERNALENTITY_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_EXTERNALENTITY_H_

#include "DfdNode.h"

class ExternalEntity : public DfdNode {
public:
  ExternalEntity(std::string name, std::pair<float, float> pos);
  ExternalEntity(uint64_t id, std::string name, std::pair<float, float> pos);
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_EXTERNALENTITY_H_
