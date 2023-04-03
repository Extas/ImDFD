#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATA_TYPE_DATATYPE_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATA_TYPE_DATATYPE_H_

#include <nlohmann/json.hpp>

class DataType {
public:
  virtual ~DataType() = default;

  [[nodiscard]] virtual std::string Serialize() const = 0;
};

class StringDataType : public DataType {
public:
  explicit StringDataType(std::string fmt) : fmt_(std::move(fmt)) {
  }

  std::string fmt_{};

  [[nodiscard]] auto Serialize() const -> std::string override {
    nlohmann::json json;
    json["type"] = "String";
    json["fmt"] = fmt_;
    return json.dump(4);
  }
};

class IntegerDataType : public DataType {
public:
  IntegerDataType(int min_value, int max_value)
      : min_value_(min_value), max_value_(max_value) {
  }

  int min_value_{};
  int max_value_{};

  [[nodiscard]] auto Serialize() const -> std::string override {
    nlohmann::json json;
    json["type"] = "Integer";
    json["min_value"] = min_value_;
    json["max_value"] = max_value_;
    return json.dump();
  }
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATA_TYPE_DATATYPE_H_
