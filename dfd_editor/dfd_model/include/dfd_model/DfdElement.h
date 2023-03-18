
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFDELEMENT_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFDELEMENT_H_

#include "Serializable.h"

#include <memory>
#include <utility>
#include <vector>

class DataFlow;

class DfdElement : public Serializable {
public:
  explicit DfdElement(std::string name) : name_(std::move(name)) {
  }

  [[nodiscard]] auto serialize() const -> std::string override {
    return {};
  }
  [[nodiscard]] auto is_valid() const -> bool override {
    return false;
  }

  std::string name_;
  std::string description_{};
  std::vector<std::shared_ptr<DataFlow>> input_data_flows_;
  std::vector<std::shared_ptr<DataFlow>> output_data_flows_;

  DfdElement(const DfdElement &other) = delete;
  DfdElement(DfdElement &&other) noexcept
      : output_data_flows_(std::move(other.output_data_flows_)),
        input_data_flows_(std::move(other.input_data_flows_)),
        name_(std::move(other.name_)) {
  }
  auto operator=(const DfdElement &other) -> DfdElement & = delete;
  auto operator=(DfdElement &&other) noexcept -> DfdElement & {
    output_data_flows_ = std::move(other.output_data_flows_);
    input_data_flows_ = std::move(other.input_data_flows_);
    name_ = std::move(other.name_);
    return *this;
  }

  virtual ~DfdElement() = default;
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFDELEMENT_H_
