#ifndef LINK_H
#define LINK_H

#include "NodeObj.h"
#include "Pin.h"

#include <algorithm>

class Link : public NodeObj {
public:
  Link(Pin *outputPin, Pin *inputPin)
      : NodeObj("Link"), m_InputPin(inputPin), m_OutputPin(outputPin) {
    m_InputPin->Connect(this);
    m_OutputPin->Connect(this);
  }

  ~Link() override {
    m_InputPin->Disconnect(this);
    m_OutputPin->Disconnect(this);
  }

  [[nodiscard]] auto GetInputPin() const -> const Pin * {
    return m_InputPin;
  }

  [[nodiscard]] auto GetOutputPin() const -> const Pin * {
    return m_OutputPin;
  }

private:
  Pin *m_InputPin;
  Pin *m_OutputPin;

public:
  Link(Link &&other) noexcept
      : NodeObj(std::move(other)), m_InputPin(other.m_InputPin),
        m_OutputPin(other.m_OutputPin) {
    other.m_InputPin = nullptr;
    other.m_OutputPin = nullptr;
  }
  auto operator=(Link &&other) noexcept -> Link & {
    if (this != &other) {
      NodeObj::operator=(std::move(other));
      m_InputPin = other.m_InputPin;
      m_OutputPin = other.m_OutputPin;
      other.m_InputPin = nullptr;
      other.m_OutputPin = nullptr;
    }
    return *this;
  }
  Link(const Link &) = delete;
  auto operator=(const Link &) -> Link & = delete;

  auto operator==(const Link &other) const -> bool {
    return GetId() == other.GetId();
  }
};

class LinkManager {
public:
  LinkManager() = default;

  [[nodiscard]] auto GetLinks() const -> const std::vector<Link> & {
    return m_Links;
  }

  void AddLink(Pin *outputPin, Pin *inputPin) {
    m_Links.emplace_back(outputPin, inputPin);
  }

  void RemoveLink(Link &link) {
    auto itor = std::find(m_Links.begin(), m_Links.end(), link);
    if (itor != m_Links.end()) {
      m_Links.erase(itor);
    }
  }

private:
  std::vector<Link> m_Links;
};

#endif // LINK_H
