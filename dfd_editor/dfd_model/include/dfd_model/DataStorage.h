
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATASTORAGE_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATASTORAGE_H_

#include "DataItem.h"
#include "DfdNode.h"
#include <functional>

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
  void RemoveDataItem(const std::shared_ptr<DataItem> &data_item);

  void UpdateDataItem(const std::shared_ptr<DataItem> &data_item) {
    auto it = std::find_if(data_items_.begin(), data_items_.end(),
        [data_item](const std::shared_ptr<DataItem> &item) {
          return item->GetElementId() == data_item->GetElementId();
        });
    if (it != data_items_.end()) {
      data_items_.erase(it);
    }
    data_items_.push_back(data_item);
  }

  [[nodiscard]] auto GetDataItems() const
      -> std::vector<std::shared_ptr<DataItem>>;

private:
  std::vector<std::shared_ptr<DataItem>> data_items_;
  DataStorage(std::string name, std::pair<float, float> pos);
  DataStorage(uint64_t id, std::string name, std::pair<float, float> pos);
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATASTORAGE_H_
