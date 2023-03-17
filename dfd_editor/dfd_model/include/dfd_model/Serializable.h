#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_SERIALIZABLE_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_SERIALIZABLE_H_

#include <string>

class Serializable {
public:
  virtual std::string serialize() const = 0;
  virtual bool is_valid() const = 0;
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_SERIALIZABLE_H_
