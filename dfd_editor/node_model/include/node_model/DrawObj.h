#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DRAWOBJ_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DRAWOBJ_H_

#include <cstdint>
#include <string>
#include <vector>

class DrawObj {
public:
  explicit DrawObj(std::string name)
      : m_Name(std::move(name)), m_Id(GetNextId()) {
  }

  virtual ~DrawObj() = default;

  virtual void Draw() const = 0;

  static auto GetNextId() -> uint64_t {
    static uint64_t s_NextId = 100;
    return s_NextId++;
  }

  [[nodiscard]] auto GetName() const -> const std::string & {
    return m_Name;
  }

  [[nodiscard]] auto GetId() const -> uint64_t {
    return m_Id;
  }

private:
  std::string m_Name;
  uint64_t m_Id = -1;

public:
  DrawObj(const DrawObj &) = delete;
  DrawObj(DrawObj &&other) noexcept
      : m_Name(std::move(other.m_Name)), m_Id(other.m_Id) {
    other.m_Id = -1;
  }
  auto operator=(DrawObj &&other) noexcept -> DrawObj & {
    if (this != &other) {
      m_Name = std::move(other.m_Name);
      m_Id = other.m_Id;
      other.m_Id = -1;
    }
    return *this;
  }

  auto operator=(const DrawObj &) -> DrawObj & = delete;
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DRAWOBJ_H_
