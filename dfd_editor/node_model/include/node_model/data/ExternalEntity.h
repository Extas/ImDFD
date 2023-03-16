
#ifndef IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODE_MODEL_EXTERNALENTITY_H_
#define IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODE_MODEL_EXTERNALENTITY_H_

#include <string>

class ExternalEntity {
public:
  ExternalEntity(const std::string &name) : m_name(name) {
  }

  const std::string &GetName() const {
    return m_name;
  }
  void SetName(const std::string &name) {
    m_name = name;
  }

  // Add more accessors, mutators, and other methods as needed

private:
  std::string m_name;
  // Add more member variables as needed
};
#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODE_MODEL_EXTERNALENTITY_H_