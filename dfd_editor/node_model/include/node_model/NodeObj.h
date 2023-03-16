#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODEOBJ_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODEOBJ_H_

#include <cstdint>
#include <string>
#include <vector>

class NodeObj {
public:
  explicit NodeObj(std::string name)
      : m_Name(std::move(name)), m_Id(GetNextId()) {
  }

  virtual ~NodeObj() = default;

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
  NodeObj(const NodeObj &) = delete;
  NodeObj(NodeObj &&other) noexcept
      : m_Name(std::move(other.m_Name)), m_Id(other.m_Id) {
    other.m_Id = -1;
  }
  auto operator=(NodeObj &&other) noexcept -> NodeObj & {
    if (this != &other) {
      m_Name = std::move(other.m_Name);
      m_Id = other.m_Id;
      other.m_Id = -1;
    }
    return *this;
  }

  auto operator=(const NodeObj &) -> NodeObj & = delete;
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_NODEOBJ_H_
