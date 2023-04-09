
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFDNODE_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFDNODE_H_

#include "Element.h"

#include <memory>
#include <utility>
#include <vector>

#include <nlohmann/json.hpp>

class DataFlow;

class DfdNode : public Element {
public:
  explicit DfdNode(std::string name, std::pair<float, float> pos,
      std::string description = "")
      : name_(std::move(name)), position_(pos),
        description_(std::move(description)) {
  }

  DfdNode(uint64_t id, std::string name, std::pair<float, float> pos,
      std::string description = "")
      : Element(id), name_(std::move(name)), position_(pos),
        description_(std::move(description)) {
  }

  void SetPosition(float x, float y) {
    position_ = {x, y};
  }

  std::string name_;
  std::pair<float, float> position_;
  std::string description_{};
  std::vector<std::weak_ptr<DataFlow>> input_data_flows_;
  std::vector<std::weak_ptr<DataFlow>> output_data_flows_;

  [[nodiscard]] auto Serialize() const -> nlohmann::json override {
    nlohmann::json json;
    json["id"] = GetElementId();
    json["name"] = name_;
    json["pos"] = {position_.first, position_.second};
    json["description"] = description_;
    return json;
  }

  [[nodiscard]] auto Serialize(const std::string &node_type) const
      -> nlohmann::json {
    nlohmann::json json;
    json["node_type"] = node_type;
    auto base_json = DfdNode::Serialize();
    json.insert(base_json.begin(), base_json.end());
    return json;
  }

  [[nodiscard]] auto IsValid() const -> bool override {
    return false;
  }

public:
  DfdNode(const DfdNode &other) = delete;
  DfdNode(DfdNode &&other) noexcept
      : Element(std::move(other)), name_(std::move(other.name_)),
        input_data_flows_(std::move(other.input_data_flows_)),
        output_data_flows_(std::move(other.output_data_flows_)) {
  }
  auto operator=(const DfdNode &other) -> DfdNode & = delete;
  auto operator=(DfdNode &&other) noexcept -> DfdNode & {
    Element::operator=(std::move(other));
    name_ = std::move(other.name_);
    input_data_flows_ = std::move(other.input_data_flows_);
    output_data_flows_ = std::move(other.output_data_flows_);
    return *this;
  }

  ~DfdNode() override = default;
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFDNODE_H_
