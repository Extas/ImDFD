#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_ELEMENT_DRAWOBJ_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_ELEMENT_DRAWOBJ_H_

#include <cstdint>
#include <string>
#include <vector>

class DrawObj {
public:
  explicit DrawObj(std::string *name) : name_(name), id_(GetNextId()) {
  }

  virtual void Draw() const = 0;

  static auto GetNextId() -> uint64_t {
    static uint64_t s_next_id = 100;
    return s_next_id++;
  }

  [[nodiscard]] auto GetName() const -> const std::string & {
    return *name_;
  }

  void SetName(const std::string &name) {
    *name_ = name;
  }

  [[nodiscard]] auto GetId() const -> uint64_t {
    return id_;
  }

private:
  std::string *name_;
  uint64_t id_ = -1;

public:
  DrawObj(DrawObj &&other) noexcept : name_(other.name_), id_(other.id_) {
    other.id_ = -1;
  }
  auto operator=(DrawObj &&other) noexcept -> DrawObj & {
    if (this != &other) {
      name_ = other.name_;
      id_ = other.id_;
      other.id_ = -1;
      other.name_ = nullptr;
    }
    return *this;
  }
  DrawObj(const DrawObj &) = delete;
  auto operator=(const DrawObj &) -> DrawObj & = delete;

  virtual ~DrawObj() = default;
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_ELEMENT_DRAWOBJ_H_
