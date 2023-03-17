
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAITEM_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAITEM_H_

#include "Serializable.h"

#include <memory>
#include <vector>

class DataItem : public Serializable {
  std::string name;
  std::string data_type;
  std::vector<std::shared_ptr<DataItem>> sub_data_items;
  // ... 其他方法，实现序列化和合法性检查
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAITEM_H_
