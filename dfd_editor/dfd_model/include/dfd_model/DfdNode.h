
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFDNODE_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFDNODE_H_

#include "Element.h"

#include <memory>
#include <utility>
#include <vector>

class DataFlow;

class DfdNode : public Element {
public:
  explicit DfdNode(std::string name, std::pair<float, float> pos)
      : position_(pos), name_(std::move(name)) {
  }

  [[nodiscard]] auto Serialize() const -> std::string override {
    return {};
  }
  [[nodiscard]] auto IsValid() const -> bool override {
    return false;
  }

  std::string name_;
  std::pair<float, float> position_;
  std::string description_{};
  std::vector<std::shared_ptr<DataFlow>> input_data_flows_;
  std::vector<std::shared_ptr<DataFlow>> output_data_flows_;

  DfdNode(const DfdNode &other) = delete;
  DfdNode(DfdNode &&other) noexcept
      : Element(std::move(other)),
        output_data_flows_(std::move(other.output_data_flows_)),
        input_data_flows_(std::move(other.input_data_flows_)),
        name_(std::move(other.name_)) {
  }
  auto operator=(const DfdNode &other) -> DfdNode & = delete;
  auto operator=(DfdNode &&other) noexcept -> DfdNode & {
    Element::operator=(std::move(other));
    output_data_flows_ = std::move(other.output_data_flows_);
    input_data_flows_ = std::move(other.input_data_flows_);
    name_ = std::move(other.name_);
    return *this;
  }

  virtual ~DfdNode() = default;
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFDNODE_H_
