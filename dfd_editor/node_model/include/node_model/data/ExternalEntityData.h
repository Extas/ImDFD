
#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_EXTERNALENTITYDATA_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_EXTERNALENTITYDATA_H_

#include <string>

class ExternalEntityData {
public:
  ExternalEntityData(const std::string &name) : name_(name) {
  }

  ExternalEntityData() : name_("ExternalEntity.name") {
  }

  [[nodiscard]] const std::string &GetName() const {
    return name_;
  }
  void SetName(const std::string &name) {
    name_ = name;
  }

  // Add more accessors, mutators, and other methods as needed

  ~ExternalEntityData() = default;

private:
  std::string name_;
  // Add more member variables as needed
};
#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_EXTERNALENTITYDATA_H_
