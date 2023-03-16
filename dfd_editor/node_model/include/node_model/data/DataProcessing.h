
#ifndef IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODE_MODEL_DATAPROCESSING_H_
#define IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODE_MODEL_DATAPROCESSING_H_

#include <string>
#include <vector>

class DataProcessing {
public:
  DataProcessing(const std::string &name) : m_name(name) {
  }

  // Accessors and mutators
  const std::string &GetName() const {
    return m_name;
  }
  void SetName(const std::string &name) {
    m_name = name;
  }

  const std::string &GetProcessingContent() const {
    return m_processingContent;
  }
  void SetProcessingContent(const std::string &content) {
    m_processingContent = content;
  }

  // Add more accessors, mutators, and other methods as needed

private:
  std::string m_name;
  std::string m_processingContent;
  // Add more member variables as needed
};

#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_NODE_MODEL_DATAPROCESSING_H_
