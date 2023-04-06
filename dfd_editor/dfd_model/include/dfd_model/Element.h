#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_ELEMENT_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_ELEMENT_H_

#include <nlohmann/json.hpp>
#include <string>

class Element {
public:
  explicit Element() : element_id_(GetNewElementId()) {
  }

  explicit Element(uint64_t special_element_id)
      : element_id_(GetNewElementId(special_element_id)) {
  }

  [[nodiscard]] virtual auto Serialize() const -> nlohmann::json = 0;
  [[nodiscard]] virtual auto IsValid() const -> bool = 0;

  Element(const Element &other) = delete;
  Element(Element &&other) noexcept = default;
  auto operator=(const Element &other) -> Element & = delete;
  auto operator=(Element &&other) noexcept -> Element & = default;

  virtual ~Element() = default;

  [[nodiscard]] auto GetElementId() const -> uint64_t {
    return element_id_;
  }

private:
  static auto GetNewElementId(uint64_t special_element_id = 0) -> uint64_t {
    static auto max_element_id = static_cast<uint64_t>(100);
    auto next_id = ++max_element_id;

    // have provided special_element_id
    if (special_element_id != 0) {
      next_id = special_element_id;
      // update max_element_id
      if (special_element_id > max_element_id) {
        max_element_id = special_element_id;
      }
    }

    return next_id;
  }

  uint64_t element_id_;
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_ELEMENT_H_
