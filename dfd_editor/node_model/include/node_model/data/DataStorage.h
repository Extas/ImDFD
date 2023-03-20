
#ifndef IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODE_MODEL_DATASTORAGE_H_
#define IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODE_MODEL_DATASTORAGE_H_

#include <string>

class DataStorage {
public:
  DataStorage(const std::string &name) : name_(name) {
  }
  DataStorage() : name_("DaaStorage.name") {
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

#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODE_MODEL_DATASTORAGE_H_
