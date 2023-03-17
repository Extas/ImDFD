#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_LINK_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_LINK_H_

#include "DrawObj.h"
#include "Pin.h"

#include <algorithm>

class Link : public DrawObj {
public:
  Link(uint64_t inputPinId, uint64_t outputPinId)
      : DrawObj("Link"), m_InputPinId(inputPinId), m_OutputPinId(outputPinId) {
  }

  void Draw() const override {
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
      : DrawObj(std::move(other)), m_InputPinId(other.m_InputPinId),
        m_OutputPinId(other.m_OutputPinId) {
    other.m_InputPinId = -1;
    other.m_OutputPinId = -1;
  }
  auto operator=(Link &&other) noexcept -> Link & {
    if (this != &other) {
      DrawObj::operator=(std::move(other));
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
    return links_;
  }

  void AddLink(uint64_t inputPinId, uint64_t outputPinId) {
    links_.emplace_back(inputPinId, outputPinId);
  }

  void RemoveLink(uint64_t linkId) {
    links_.erase(
        std::remove_if(links_.begin(), links_.end(),
            [linkId](const Link &link) { return link.GetId() == linkId; }),
        links_.end());
  }

private:
  std::vector<Link> links_;
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_LINK_H_