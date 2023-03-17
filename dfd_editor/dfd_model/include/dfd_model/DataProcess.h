
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAPROCESS_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAPROCESS_H_

#include "DFDElement.h"

class DFD;

class DataProcess : public DFDElement {
  std::string process_description;
  std::shared_ptr<DFD> sub_dfd;
  // ... 其他方法，实现序列化和合法性检查
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAPROCESS_H_
