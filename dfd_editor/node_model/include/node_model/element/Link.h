#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_ELEMENT_LINK_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_ELEMENT_LINK_H_

#include "DrawObj.h"
#include "Pin.h"

#include <algorithm>
#include <logging/Logger.h>
#include <stdint.h>

class Link {
public:
  Link(uint64_t link_id, uint64_t input_pin_id, uint64_t output_pin_id)
      : link_id_(link_id), input_pin_id_(input_pin_id),
        output_pin_id_(output_pin_id) {
  }

  void Draw() const {
  }

  [[nodiscard]] auto GetInputPinId() const -> uint64_t {
    return input_pin_id_;
  }

  [[nodiscard]] auto GetOutputPinId() const -> uint64_t {
    return output_pin_id_;
  }

  [[nodiscard]] auto GetId() const -> uint64_t {
    return link_id_;
  }

private:
  uint64_t link_id_;
  uint64_t input_pin_id_;
  uint64_t output_pin_id_;

public:
  Link(Link &&other) noexcept
      : link_id_(other.link_id_), input_pin_id_(other.input_pin_id_),
        output_pin_id_(other.output_pin_id_) {
    other.link_id_ = static_cast<uint64_t>(0);
    other.input_pin_id_ = static_cast<uint64_t>(0);
    other.output_pin_id_ = static_cast<uint64_t>(0);
  }
  auto operator=(Link &&other) noexcept -> Link & {
    if (this != &other) {
      link_id_ = other.link_id_;
      input_pin_id_ = other.input_pin_id_;
      output_pin_id_ = other.output_pin_id_;

      other.link_id_ = static_cast<uint64_t>(0);
      other.input_pin_id_ = static_cast<uint64_t>(0);
      other.output_pin_id_ = static_cast<uint64_t>(0);
    }
    return *this;
  }

  Link(const Link &) = delete;
  auto operator=(const Link &) -> Link & = delete;

  auto operator==(const Link &other) const -> bool {
    return input_pin_id_ == other.input_pin_id_ &&
           output_pin_id_ == other.output_pin_id_;
  }

  ~Link() = default;
};

class LinkManager {
public:
  LinkManager() = default;

  [[nodiscard]] auto GetLinks() const -> const std::vector<Link> & {
    return links_;
  }

  void AddLink(
      uint64_t link_id, uint64_t input_pin_id, uint64_t output_pin_id) {
    links_.emplace_back(link_id, input_pin_id, output_pin_id);
  }

  void RemoveLink(uint64_t link_id) {
    links_.erase(
        std::remove_if(links_.begin(), links_.end(),
            [link_id](const Link &link) { return link.GetId() == link_id; }),
        links_.end());
  }

  void ClearLinks() {
    links_.clear();
  }

private:
  std::vector<Link> links_;
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_ELEMENT_LINK_H_
