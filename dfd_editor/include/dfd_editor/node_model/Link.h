#ifndef LINK_H
#define LINK_H

#include "NodeObj.h"
#include "Pin.h"

#include <algorithm>

class Link : public NodeObj {
public:
  Link(uint64_t inputPinId, uint64_t outputPinId)
      : NodeObj("Link"), m_InputPinId(inputPinId), m_OutputPinId(outputPinId) {
  }

  [[nodiscard]] auto GetInputPinId() const -> uint64_t {
    return m_InputPinId;
  }

  [[nodiscard]] auto GetOutputPinId() const -> uint64_t {
    return m_OutputPinId;
  }

private:
  uint64_t m_InputPinId;
  uint64_t m_OutputPinId;

public:
  Link(Link &&other) noexcept
      : NodeObj(std::move(other)), m_InputPinId(other.m_InputPinId),
        m_OutputPinId(other.m_OutputPinId) {
    other.m_InputPinId = -1;
    other.m_OutputPinId = -1;
  }
  auto operator=(Link &&other) noexcept -> Link & {
    if (this != &other) {
      NodeObj::operator=(std::move(other));
      m_InputPinId = other.m_InputPinId;
      m_OutputPinId = other.m_OutputPinId;
      other.m_InputPinId = -1;
      other.m_OutputPinId = -1;
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

  void AddLink(uint64_t inputPinId, uint64_t outputPinId) {
    m_Links.emplace_back(inputPinId, outputPinId);
  }

  void RemoveLink(uint64_t linkId) {
    m_Links.erase(
        std::remove_if(m_Links.begin(), m_Links.end(),
            [linkId](const Link &link) { return link.GetId() == linkId; }),
        m_Links.end());
  }

private:
  std::vector<Link> m_Links;
};

#endif // LINK_H
