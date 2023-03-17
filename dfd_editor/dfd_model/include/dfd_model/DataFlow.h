
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAFLOW_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAFLOW_H_

#include "DataItem.h"
#include "Serializable.h"

#include <memory>
#include <vector>

class DFDElement;

class DataFlow : public Serializable {
  std::string name;
  std::vector<std::shared_ptr<DataItem>> data_items;
  std::shared_ptr<DFDElement> source;
  std::shared_ptr<DFDElement> target;
  // ... 其他方法，实现序列化和合法性检查
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAFLOW_H_
