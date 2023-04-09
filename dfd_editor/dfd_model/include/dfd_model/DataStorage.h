
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATASTORAGE_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATASTORAGE_H_

#include "DataItem.h"
#include "DfdNode.h"

class DataStorage : public DfdNode {
public:
  static auto Create(std::string name, std::pair<float, float> pos)
      -> std::shared_ptr<DataStorage>;
  static auto Create(uint64_t id, std::string name, std::pair<float, float> pos)
      -> std::shared_ptr<DataStorage>;

  [[nodiscard]] auto Serialize() const -> nlohmann::json override;
  [[nodiscard]] static auto DeSerialize(nlohmann::json json)
      -> std::shared_ptr<DataStorage>;

  void AddDataItem(std::shared_ptr<DataItem> data_item);

  std::vector<std::shared_ptr<DataItem>> stored_data_items_;

private:
  DataStorage(std::string name, std::pair<float, float> pos);
  DataStorage(uint64_t id, std::string name, std::pair<float, float> pos);
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATASTORAGE_H_
