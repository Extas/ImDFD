#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_ELEMENT_DRAWOBJ_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_ELEMENT_DRAWOBJ_H_

#include <cstdint>
#include <string>
#include <vector>

class DrawObj {
public:
  explicit DrawObj(uint64_t obj_id, std::string *name)
      : id_(obj_id), name_(name) {
  }

  virtual void Draw() const = 0;

  [[nodiscard]] auto GetName() const -> const std::string & {
    return *name_;
  }
  void SetName(std::string *name) {
    name_ = name;
  }

  [[nodiscard]] auto GetId() const -> uint64_t {
    return id_;
  }

private:
  uint64_t id_ = static_cast<uint64_t>(0);
  std::string *name_;

public:
  DrawObj(DrawObj &&other) noexcept : id_(other.id_), name_(other.name_) {
    other.id_ = static_cast<uint64_t>(0);
    ;
  }
  auto operator=(DrawObj &&other) noexcept -> DrawObj & {
    if (this != &other) {
      name_ = other.name_;
      id_ = other.id_;
      other.id_ = static_cast<uint64_t>(0);
      ;
      other.name_ = nullptr;
    }
    return *this;
  }
  DrawObj(const DrawObj &) = delete;
  auto operator=(const DrawObj &) -> DrawObj & = delete;

  virtual ~DrawObj() = default;
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_ELEMENT_DRAWOBJ_H_
