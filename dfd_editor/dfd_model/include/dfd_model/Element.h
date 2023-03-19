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

  [[nodiscard]] auto GetElementId() const -> int {
    return element_id_;
  }

private:
  static auto GetNewElementId() -> int {
    static int element_id = 0;
    return element_id++;
  }
  int element_id_;
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_ELEMENT_H_
