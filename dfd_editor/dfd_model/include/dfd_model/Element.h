#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_ELEMENT_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_ELEMENT_H_

#include <string>

class Element {
public:
  explicit Element() : element_id_(GetNewElementId()) {
  }
  [[nodiscard]] virtual auto Serialize() const -> std::string = 0;
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
  static auto GetNewElementId() -> uint64_t {
    static uint64_t element_id = static_cast<uint64_t>(100);
    ;
    return element_id++;
  }
  uint64_t element_id_;
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_ELEMENT_H_
