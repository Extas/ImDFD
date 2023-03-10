#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>
#include <vector>

enum class ElementType { Input, Output, Process, External, Storage };

class Element {
public:
  Element(ElementType type, std::string name)
      : m_type(type), m_name(std::move(name)) {
  }

  virtual ~Element() = default;

  const std::string &GetName() const;
  ElementType GetType() const {
    return m_type;
  }

  // Get the inputs of this element
  virtual std::vector<Element *> GetInputs() const = 0;

  // Get the outputs of this element
  virtual std::vector<Element *> GetOutputs() const = 0;

  // Get the data produced by this element (e.g. for output elements)
  virtual std::vector<std::string> GetDataProduced() const {
    return {};
  }

  // Get the data required by this element (e.g. for input elements)
  virtual std::vector<std::string> GetDataRequired() const {
    return {};
  }

private:
  ElementType m_type;
  std::string m_name;
};

#endif // ELEMENT_H
