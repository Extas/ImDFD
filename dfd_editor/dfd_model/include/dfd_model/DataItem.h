
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAITEM_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAITEM_H_

#include "Element.h"

#include <memory>
#include <optional>
#include <set>
#include <vector>

class DataItem : public Element {
public:
  using DataDescription = std::string;
  using DataValueType = std::string;
  using DataValue = std::string;
  using DataMap =
      std::map<DataDescription, std::pair<DataValueType, DataValue>>;

  static auto CreateStringDataItem(std::string name, std::string fmt)
      -> std::shared_ptr<DataItem>;
  static auto CreateStringDataItemWithId(uint64_t id, std::string name,
      std::string fmt) -> std::shared_ptr<DataItem>;
  static auto CreateIntegerDataItem(std::string name, int min_value,
      int max_value) -> std::shared_ptr<DataItem>;
  static auto CreateIntegerDataItemWithId(uint64_t id, std::string name,
      int min_value, int max_value) -> std::shared_ptr<DataItem>;

  virtual void AddData() = 0;

  [[nodiscard]] auto Serialize() const -> nlohmann::json override;
  [[nodiscard]] static auto DeSerialize(nlohmann::json json)
      -> std::shared_ptr<DataItem>;
  [[nodiscard]] auto IsValid() const -> bool override;

  [[nodiscard]] auto GetName()
      -> std::optional<std::reference_wrapper<std::string>> {
    return name_;
  }

  [[nodiscard]] static auto GetDerivedTypeNames() -> std::set<std::string> {
    return all_type_names_;
  }

  [[nodiscard]] auto GetDateTypeName() const -> std::string {
    return date_type_name_;
  }

  [[nodiscard]] auto GetDataMap() const -> DataMap {
    return data_map_;
  }

protected:
  DataItem(std::string name, std::string type_name)
      : name_(std::move(name)), date_type_name_(std::move(type_name)) {
  }

  DataItem(uint64_t id, std::string name, std::string type_name)
      : Element(id), name_(std::move(name)),
        date_type_name_(std::move(type_name)) {
  }

  std::string name_;
  std::string date_type_name_;
  DataMap data_map_;
  std::vector<std::shared_ptr<DataItem>> sub_data_items_;

  inline static std::set<std::string> all_type_names_;
};

class StringDataItem : public DataItem {
public:
  StringDataItem(std::string name, std::string fmt)
      : DataItem(std::move(name), "string"), fmt_(std::move(fmt)) {
    const auto *date_type_name = "string";
    all_type_names_.insert(date_type_name);
  }

  StringDataItem(uint64_t id, std::string name, std::string fmt)
      : DataItem(id, std::move(name), "string"), fmt_(std::move(fmt)) {
    const auto *date_type_name = "string";
    all_type_names_.insert(date_type_name);
  }

  void AddData() override {
    data_map_.insert(
        {DataDescription("format"), {DataValueType("string"), fmt_}});
  }

  [[nodiscard]] auto Serialize() const -> nlohmann::json override;
  [[nodiscard]] static auto DeSerialize(nlohmann::json json)
      -> std::shared_ptr<StringDataItem>;
  [[nodiscard]] auto IsValid() const -> bool override {
    return DataItem::IsValid();
  }

  std::string fmt_{};
};

class IntegerDataItem : public DataItem {
public:
  IntegerDataItem(std::string name, int min_value, int max_value)
      : DataItem(std::move(name), "integer"), min_value_(min_value),
        max_value_(max_value) {
    const auto *date_type_name = "integer";
    all_type_names_.insert(date_type_name);
  }

  IntegerDataItem(uint64_t id, std::string name, int min_value, int max_value)
      : DataItem(id, std::move(name), "integer"), min_value_(min_value),
        max_value_(max_value) {
    const auto *date_type_name = "integer";
    all_type_names_.insert(date_type_name);
  }

  void AddData() override {
    data_map_.insert({DataDescription("min_value"),
        {DataValueType("integer"), std::to_string(min_value_)}});
    data_map_.insert({DataDescription("max_value"),
        {DataValueType("integer"), std::to_string(max_value_)}});
  }

  [[nodiscard]] auto Serialize() const -> nlohmann::json override;
  [[nodiscard]] static auto DeSerialize(nlohmann::json json)
      -> std::shared_ptr<IntegerDataItem>;
  [[nodiscard]] auto IsValid() const -> bool override {
    return DataItem::IsValid();
  }

  int min_value_{};
  int max_value_{};
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAITEM_H_
