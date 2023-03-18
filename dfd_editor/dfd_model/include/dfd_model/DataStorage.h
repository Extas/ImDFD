
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATASTORAGE_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATASTORAGE_H_

#include "DataItem.h"
#include "DfdNode.h"

class DataStorage : public DfdNode {
public:
  DataStorage(std::string name, std::pair<float, float> pos);
  std::vector<std::shared_ptr<DataItem>> stored_data_items_;
  // ... 其他方法，实现序列化和合法性检查
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATASTORAGE_H_
