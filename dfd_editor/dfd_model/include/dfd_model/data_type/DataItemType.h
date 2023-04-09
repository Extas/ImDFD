#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATA_TYPE_DATAITEMTYPE_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATA_TYPE_DATAITEMTYPE_H_

#include <nlohmann/json.hpp>

class DataItemType {
public:
  virtual ~DataItemType() = default;

  [[nodiscard]] virtual auto Serialize() const -> nlohmann::json = 0;
  [[nodiscard]] static auto DeSerialize(nlohmann::json json)
      -> std::shared_ptr<DataItemType>;

  [[nodiscard]] static std::vector<std::string> GetDerivedTypeNames() {
    return type_names_;
  }

  inline static std::vector<std::string> type_names_;
};

class StringDataType : public DataItemType {
public:
  explicit StringDataType(std::string fmt) : fmt_(std::move(fmt)) {
    type_names_.push_back("string");
  }

  std::string fmt_{};

  [[nodiscard]] auto Serialize() const -> nlohmann::json override {
    nlohmann::json json;
    json["type"] = "string";
    json["fmt"] = fmt_;
    return json;
  }
  [[nodiscard]] static auto DeSerialize(nlohmann::json json)
      -> std::shared_ptr<StringDataType> {
    return std::make_shared<StringDataType>(json["fmt"].get<std::string>());
  }
};

class IntegerDataType : public DataItemType {
public:
  IntegerDataType(int min_value, int max_value)
      : min_value_(min_value), max_value_(max_value) {
    type_names_.push_back("integer");
  }

  int min_value_{};
  int max_value_{};

  [[nodiscard]] auto Serialize() const -> nlohmann::json override {
    nlohmann::json json;
    json["type"] = "integer";
    json["min_value"] = min_value_;
    json["max_value"] = max_value_;
    return json;
  }
  [[nodiscard]] static auto DeSerialize(nlohmann::json json)
      -> std::shared_ptr<IntegerDataType> {
    return std::make_shared<IntegerDataType>(
        json["min_value"].get<int>(), json["max_value"].get<int>());
  }
};
#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATA_TYPE_DATAITEMTYPE_H_
