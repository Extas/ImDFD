#include <functional>
#include <node_model/DataStorageNode.h>
#include <node_model/ExternalEntityNode.h>
#include <node_model/NodeManager.h>

class Dfd;

auto NodeManager::AddNode(
    uint64_t node_id, std::string *name, std::pair<float, float> *position) {
  auto node = std::make_shared<Node>(node_id, name, position);
  nodes_.push_back(node);
  return node;
}

auto NodeManager::AddDataProcessNode(uint64_t node_id, std::string *name,
    std::pair<float, float> *position, std::string *description,
    const std::shared_ptr<Dfd> &sub_dfd) -> std::shared_ptr<DataProcessNode> {

  int64_t get_canvas_id = -1;
  SignalHandel::Instance().create_new_dfd_(sub_dfd, get_canvas_id);

  auto node = std::make_shared<DataProcessNode>(
      node_id, name, position, description, get_canvas_id);
  nodes_.push_back(node);
  return node;
}
auto NodeManager::AddExternalEntityNode(uint64_t node_id, std::string *name,
    std::pair<float, float> *position) -> std::shared_ptr<ExternalEntityNode> {
  auto node = std::make_shared<ExternalEntityNode>(node_id, name, position);
  nodes_.push_back(node);
  return node;
}
auto NodeManager::AddDataStorageNode(uint64_t node_id, std::string *name,
    std::pair<float, float> *position) -> std::shared_ptr<DataStorageNode> {
  auto node = std::make_shared<DataStorageNode>(node_id, name, position);
  nodes_.push_back(node);
  return node;
}

void NodeManager::RemoveNode(uint64_t node_id) {
  for (auto &node_ptr : nodes_) {
    if (node_ptr->GetId() == node_id) {
      node_ptr = std::move(nodes_.back());
      nodes_.pop_back();
      return;
    }
  }
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
auto NodeManager::GetPinById(uint64_t pin_id) const
    -> std::optional<std::reference_wrapper<const Pin>> {
  for (const auto &kNodePtr : nodes_) {
    if (auto pin = kNodePtr->GetPin(pin_id)) {
      return pin;
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
