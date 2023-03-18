
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAPROCESS_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAPROCESS_H_

#include "DfdElement.h"

class Dfd;

class DataProcess : public DfdElement {
public:
  DataProcess(std::string name);
  std::string process_description_;
  std::shared_ptr<Dfd> sub_dfd_;
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAPROCESS_H_
