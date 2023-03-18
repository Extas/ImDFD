#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATA_TYPE_DATATYPE_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATA_TYPE_DATATYPE_H_

class DataType {
public:
  //  enum class Type {
  //    Integer,
  //    Real,
  //    Time,
  //    Currency,
  //    String
  //  };

  explicit DataType(std::string type) : type_(std::move(type)) {
  }

  std::string type_{};
};

class StringDataType : public DataType {
public:
  StringDataType() : DataType("String"), fmt_() {
  }

  std::string fmt_{};
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATA_TYPE_DATATYPE_H_
