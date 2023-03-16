#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DRAWOBJ_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DRAWOBJ_H_

#include <cstdint>
#include <string>
#include <vector>

class DrawObj {
public:
  explicit DrawObj(std::string name)
      : name_(std::move(name)), id_(GetNextId()) {
  }

  virtual ~DrawObj() = default;

  virtual void Draw() const = 0;

  static auto GetNextId() -> uint64_t {
    static uint64_t s_NextId = 100;
    return s_NextId++;
  }

  [[nodiscard]] auto GetName() const -> const std::string & {
    return name_;
  }

  void SetName(const std::string &name) {
    name_ = name;
  }

  [[nodiscard]] auto GetId() const -> uint64_t {
    return id_;
  }

private:
  std::string name_;
  uint64_t id_ = -1;

public:
  DrawObj(const DrawObj &) = delete;
  DrawObj(DrawObj &&other) noexcept
      : name_(std::move(other.name_)), id_(other.id_) {
    other.id_ = -1;
  }
  auto operator=(DrawObj &&other) noexcept -> DrawObj & {
    if (this != &other) {
      name_ = std::move(other.name_);
      id_ = other.id_;
      other.id_ = -1;
    }
    return *this;
  }

  auto operator=(const DrawObj &) -> DrawObj & = delete;
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DRAWOBJ_H_
