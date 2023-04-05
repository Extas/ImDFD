#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFD_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFD_H_

#include "Element.h"

#include "DataFlow.h"
#include "DataItem.h"
#include "DataProcess.h"
#include "DataStorage.h"
#include "ExternalEntity.h"

class Dfd : public Element {
public:
  explicit Dfd(std::string name);
  Dfd(uint64_t id, std::string name);
  std::vector<std::shared_ptr<DataFlow>> data_flows_;
  std::vector<std::shared_ptr<DataItem>> data_items_;
  std::vector<std::shared_ptr<DataProcess>> data_processes_;
  std::vector<std::shared_ptr<ExternalEntity>> external_entities_;
  std::vector<std::shared_ptr<DataStorage>> data_storages_;

  void CreateTestData();

  [[nodiscard]] auto GetJsonString() const -> std::string;

  [[nodiscard]] auto Serialize() const -> nlohmann::json override;
  [[nodiscard]] auto IsValid() const -> bool override;

  std::string name_;
};
#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFD_H_
