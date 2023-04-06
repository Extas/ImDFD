
#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_DATASTORAGEDATA_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_DATASTORAGEDATA_H_

#include <string>

class DataStorageData {
public:
  DataStorageData(const std::string &name) : name_(name) {
  }
  DataStorageData() : name_("DaaStorage.name") {
  }

  const std::string &GetName() const {
    return name_;
  }
  void SetName(const std::string &name) {
    name_ = name;
  }

  // Add more accessors, mutators, and other methods as needed

private:
  std::string name_;
  // Add more member variables as needed
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_DATASTORAGEDATA_H_
