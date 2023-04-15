
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAITEM_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAITEM_H_

#include "Element.h"

#include <memory>
#include <nlohmann/json.hpp>
#include <optional>
#include <set>
#include <vector>

class DataFlow;

class DataItem : public Element {
public:
  using DataDescription = std::string;
  using DataValueType = std::string;
  using DataValue = std::string;

  static auto CreateDataItem(std::string name, std::string type_name)
      -> std::shared_ptr<DataItem>;

  static auto CreateDataItemWithId(uint64_t id, std::string name,
      std::string type_name) -> std::shared_ptr<DataItem>;

  void AddDataDef(DataDescription data_description,
      DataValueType data_value_type, DataValue data_value);

  void AddSubDataItem(std::shared_ptr<DataItem> sub_data_item) {
    sub_data_items_.push_back(std::move(sub_data_item));
  }

  void AddDataFlow(std::shared_ptr<DataFlow> data_flow) {
    data_flows_.push_back(std::move(data_flow));
  }

  void DeleteDataFlow(std::shared_ptr<DataFlow> data_flow) {
    data_flows_.erase(
        std::remove(data_flows_.begin(), data_flows_.end(), data_flow),
        data_flows_.end());
  }

  void SetDataJson(nlohmann::json data_json) {
    this->data_json_ = data_json;
  }

  [[nodiscard]] auto Serialize() const -> nlohmann::json override;
  [[nodiscard]] static auto Deserialize(nlohmann::json json)
      -> std::shared_ptr<DataItem>;
  [[nodiscard]] auto IsValid() const -> bool override;

  [[nodiscard]] auto GetName()
      -> std::optional<std::reference_wrapper<std::string>> {
    return name_;
  }

  [[nodiscard]] static auto GetDerivedTypeNames() -> std::set<std::string> {
    return all_type_names_;
  }

  [[nodiscard]] auto GetDateTypeName()
      -> std::optional<std::reference_wrapper<std::string>> {
    return data_type_name_;
  }

  [[nodiscard]] static auto GetAllItems()
      -> std::vector<std::shared_ptr<DataItem>> {

    all_items_.erase(std::remove_if(all_items_.begin(), all_items_.end(),
                         [](const std::shared_ptr<DataItem> &item) {
                           return item->GetDataFlows().empty();
                         }),
        all_items_.end());
    return all_items_;
  }

  [[nodiscard]] auto GetSubDataItems() const
      -> std::vector<std::shared_ptr<DataItem>> {
    return sub_data_items_;
  }

  [[nodiscard]] auto GetDataJson() const -> nlohmann::json {
    return data_json_;
  }

  [[nodiscard]] auto GetDataFlows() const
      -> std::vector<std::shared_ptr<DataFlow>> {
    return data_flows_;
  }

  DataItem(std::string name, std::string type_name)
      : name_(std::move(name)), data_type_name_(std::move(type_name)) {
  }

  DataItem(uint64_t id, std::string name, std::string type_name)
      : Element(id), name_(std::move(name)),
        data_type_name_(std::move(type_name)) {
  }

private:
  std::string name_;
  std::string data_type_name_;
  nlohmann::json data_json_;
  std::vector<std::shared_ptr<DataItem>> sub_data_items_;

  std::vector<std::shared_ptr<DataFlow>> data_flows_;

  inline static std::set<std::string> all_type_names_;
  inline static std::vector<std::shared_ptr<DataItem>> all_items_;
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAITEM_H_
