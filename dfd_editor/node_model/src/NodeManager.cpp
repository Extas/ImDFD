#include <functional>
#include <node_model/DataStorageNode.h>
#include <node_model/ExternalEntityNode.h>
#include <node_model/NodeManager.h>

#include <logging/Logger.h>

auto NodeManager::AddNode(std::shared_ptr<Node> node) -> std::shared_ptr<Node> {
  nodes_.push_back(node);
  return node;
}

auto NodeManager::AddDataProcessNode(uint64_t node_id, std::string *name,
    std::pair<float, float> *position, std::string *description,
    uint64_t sub_dfd_id) -> std::shared_ptr<DataProcessNode> {

  auto node = std::make_shared<DataProcessNode>(
      node_id, name, position, description, sub_dfd_id);
  uint64_t input_pin_id = (node_id << 16) + 1ULL;
  node->AddInputPin(input_pin_id, nullptr);
  uint64_t output_pin_id = input_pin_id + 1ULL;
  node->AddOutputPin(output_pin_id, nullptr);
  AddNode(node);
  return node;
}
auto NodeManager::AddExternalEntityNode(uint64_t node_id, std::string *name,
    std::pair<float, float> *position) -> std::shared_ptr<ExternalEntityNode> {
  auto node = std::make_shared<ExternalEntityNode>(node_id, name, position);
  node->AddOutputPin((node_id << 16) + 1ULL, nullptr);
  AddNode(node);
  return node;
}
auto NodeManager::AddDataStorageNode(uint64_t node_id, std::string *name,
    std::pair<float, float> *position) -> std::shared_ptr<DataStorageNode> {
  auto node = std::make_shared<DataStorageNode>(node_id, name, position);
  node->AddInputPin((node_id << 16) + 1ULL, nullptr);
  AddNode(node);
  return node;
}

auto NodeManager::GetNode(uint64_t node_id)
    -> std::optional<std::reference_wrapper<Node>> {
  for (auto &node_ptr : nodes_) {
    if (node_ptr->GetId() == node_id) {
      return std::ref(*node_ptr);
    }
  }
  return std::nullopt;
}

auto NodeManager::GetNodes() const -> const std::vector<std::shared_ptr<Node>> {
  return nodes_;
}

auto NodeManager::GetNodeByPinId(uint64_t pin_id) const
    -> std::optional<std::reference_wrapper<Node>> {
  for (const auto &kNodePtr : nodes_) {
    if (auto pin = kNodePtr->GetPin(pin_id)) {
      return std::ref(*kNodePtr);
    }
  }
  return std::nullopt;
}

auto NodeManager::GetInputPinById(uint64_t pin_id) const
    -> std::optional<std::reference_wrapper<const InPin>> {
  for (const auto &kNodePtr : nodes_) {
    if (auto pin = kNodePtr->GetInputPin(pin_id)) {
      return pin;
    }
  }
  return std::nullopt;
}

auto NodeManager::GetOutputPinById(uint64_t pin_id) const
    -> std::optional<std::reference_wrapper<const OutPin>> {
  for (const auto &kNodePtr : nodes_) {
    if (auto pin = kNodePtr->GetOutputPin(pin_id)) {
      return pin;
    }
  }
  return std::nullopt;
}

auto NodeManager::ClearNodes() -> void {
  nodes_.clear();
}
