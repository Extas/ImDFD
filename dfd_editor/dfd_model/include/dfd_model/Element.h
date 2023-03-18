#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_ELEMENT_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_ELEMENT_H_

#include <string>

class Element {
public:
  explicit Element(std::pair<float, float> pos)
      : element_id_(GetNewElementId()), position_(pos) {
  }
  [[nodiscard]] virtual auto Serialize() const -> std::string = 0;
  [[nodiscard]] virtual auto IsValid() const -> bool = 0;

  [[nodiscard]] auto GetElementId() const -> int {
    return element_id_;
  }

  Element(const Element &other) = delete;
  Element(Element &&other) noexcept = default;
  auto operator=(const Element &other) -> Element & = delete;
  auto operator=(Element &&other) noexcept -> Element & = default;

  virtual ~Element() = default;

  std::pair<float, float> position_;

private:
  static auto GetNewElementId() -> int {
    static int element_id = 0;
    return element_id++;
  }
  int element_id_;
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_ELEMENT_H_
