#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFD_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFD_H_

#include "Serializable.h"

#include <memory>
#include <vector>

class DataFlow;
class DataItem;
class DataProcessData;
class ExternalEntity;
class DataStorage;

class DFD : public Serializable {
  std::vector<std::shared_ptr<DataFlow>> data_flows;
  std::vector<std::shared_ptr<DataItem>> data_items;
  std::vector<std::shared_ptr<DataProcessData>> data_processes;
  std::vector<std::shared_ptr<ExternalEntity>> external_entities;
  std::vector<std::shared_ptr<DataStorage>> data_storages;
  // ... 其他方法，实现序列化和合法性检查
};
#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFD_H_
