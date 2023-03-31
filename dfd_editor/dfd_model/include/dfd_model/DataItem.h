
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAITEM_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAITEM_H_

#include "Element.h"
#include "data_type/DataType.h"

#include <memory>
#include <vector>

class DataItem : public Element {
public:
  static auto CreateIntegerDataItem(std::string name, int min_value,
      int max_value) -> std::shared_ptr<DataItem> {
    auto data_type = std::make_unique<IntegerDataType>(min_value, max_value);
    return std::make_shared<DataItem>(
        DataItem(std::move(name), std::move(data_type)));
  }

  static auto CreateStringDataItem(std::string name, std::string fmt)
      -> std::shared_ptr<DataItem> {
    auto data_type = std::make_unique<StringDataType>(std::move(fmt));
    return std::make_shared<DataItem>(
        DataItem(std::move(name), std::move(data_type)));
  }

  [[nodiscard]] auto Serialize() const -> std::string override;
  [[nodiscard]] auto IsValid() const -> bool override;

private:
  DataItem(std::string name, std::unique_ptr<DataType> data_type)
      : name_(std::move(name)), data_type_(std::move(data_type)) {
  }

  DataItem(uint64_t id, std::string name, std::unique_ptr<DataType> data_type)
      : Element(id), name_(std::move(name)), data_type_(std::move(data_type)) {
  }

  std::string name_;
  std::unique_ptr<DataType> data_type_;

  std::vector<std::shared_ptr<DataItem>> sub_data_items_;
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAITEM_H_
