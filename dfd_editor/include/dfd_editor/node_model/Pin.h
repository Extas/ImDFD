#ifndef PIN_HPP
#define PIN_HPP

#include "NodeObj.h"
#include <string>
#include <utility>
#include <vector>

class Node;
class Link;

class Pin : public NodeObj {
public:
  explicit Pin(std::string name) : NodeObj(std::move(name)) {
  }

  ~Pin() override = default;

  [[nodiscard]] virtual auto IsConnected() const -> bool {
    return !m_Links.empty();
  }

  [[nodiscard]] auto GetName() const -> const std::string & {
    return NodeObj::GetName();
  }

  void Connect(Link *link) {
    m_Links.push_back(link);
  }

  void Disconnect(Link *link) {
    m_Links.erase(
        std::remove(m_Links.begin(), m_Links.end(), link), m_Links.end());
  }

  [[nodiscard]] auto GetLinks() const -> const std::vector<Link *> & {
    return m_Links;
  }

  [[nodiscard]] auto GetParentNode() const -> const Node * {
    return m_ParentNode;
  }

  void SetParentNode(Node *parentNode) {
    m_ParentNode = parentNode;
  }

private:
  std::vector<Link *> m_Links;
  Node *m_ParentNode = nullptr;

public:
  Pin(const Pin &) = delete;
  Pin(Pin &&) noexcept = default;
  auto operator=(const Pin &) -> Pin & = delete;
  auto operator=(Pin &&) -> Pin & = delete;
};

class OutPin : public Pin {
public:
  using Pin::Pin;

  // TODO(Pin): Add other functionality specific to out pin if necessary
};

class InPin : public Pin {
public:
  using Pin::Pin;

  // TODO(Pin): Add other functionality specific to in pin if necessary
};

#endif // PIN_HPP
