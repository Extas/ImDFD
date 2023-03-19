#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFD_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFD_H_

#include "Element.h"

#include "DataFlow.h"
#include "DataItem.h"
#include "DataProcess.h"
#include "DataStorage.h"
#include "ExternalEntity.h"

class Dfd {
public:
  Dfd(std::string name);
  std::vector<std::shared_ptr<DataFlow>> data_flows_;
  std::vector<std::shared_ptr<DataItem>> data_items_;
  std::vector<std::shared_ptr<DataProcess>> data_processes_;
  std::vector<std::shared_ptr<ExternalEntity>> external_entities_;
  std::vector<std::shared_ptr<DataStorage>> data_storages_;

  void CreateTestData(); // 从外部实体到数据处理到数据存储

  [[nodiscard]] static auto Serialize() -> std::string;
  [[nodiscard]] static auto IsValid() -> bool;

  std::string name_;
};
#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFD_H_