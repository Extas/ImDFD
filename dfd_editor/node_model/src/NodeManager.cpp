#include <functional>
#include <node_model/NodeManager.h>

void NodeManager::SetOpenDFDCallback(std::function<void()> callback) {
  open_dfd_callback_ = std::move(callback);
}

void NodeManager::AddNode(std::string name, std::pair<float, float> position) {
  nodes_.push_back(std::make_unique<Node>(std::move(name), position));
}

void NodeManager::AddNode(std::string name) {
  AddNode(std::move(name), std::make_pair(0, 0));
}

void NodeManager::AddDataProcessNode(const std::string &name,
    std::pair<float, float> position, const DataProcess &data_processing) {

  nodes_.push_back(
      std::make_unique<DataProcessNode>(name, position, data_processing));

  auto *node = dynamic_cast<DataProcessNode *>(nodes_.back().get());
  if (node != nullptr) {
    node->SetOpenDFDCallback(open_dfd_callback_);
  }
}

void NodeManager::AddInputPin(std::string name) {
  nodes_.back()->AddInputPin(std::move(name));
}

void NodeManager::AddInputPin(std::string name, int node_id) {
  if (auto node = GetNode(node_id)) {
    if (node.has_value()) {
      node->get().AddInputPin(std::move(name));
    }
  }
}

void NodeManager::AddOutputPin(std::string name) {
  nodes_.back()->AddOutputPin(std::move(name));
}

void NodeManager::AddOutputPin(std::string name, int node_id) {
  if (auto node = GetNode(node_id)) {
    if (node.has_value()) {
      node->get().AddOutputPin(std::move(name));
    }
  }
}

void NodeManager::RemoveNode(int node_id) {
  for (auto &node_ptr : nodes_) {
    if (node_ptr->GetId() == node_id) {
      node_ptr = std::move(nodes_.back());
      nodes_.pop_back();
      return;
    }
  }
}

auto NodeManager::GetNode(int node_id)
    -> std::optional<std::reference_wrapper<Node>> {
  for (auto &node_ptr : nodes_) {
    if (node_ptr->GetId() == node_id) {
      return std::ref(*node_ptr);
    }
  }
  return std::nullopt;
}

auto NodeManager::GetPinById(int pin_id) const
    -> std::optional<std::reference_wrapper<const Pin>> {
  for (const auto &kNodePtr : nodes_) {
    if (auto pin = kNodePtr->GetPin(pin_id)) {
      return pin;
    }
  }
  return std::nullopt;
}

auto NodeManager::GetInputPinById(int pin_id) const
    -> std::optional<std::reference_wrapper<const InPin>> {
  for (const auto &kNodePtr : nodes_) {
    if (auto pin = kNodePtr->GetInputPin(pin_id)) {
      return pin;
    }
  }
  return std::nullopt;
}

auto NodeManager::GetOutputPinById(int pin_id) const
    -> std::optional<std::reference_wrapper<const OutPin>> {
  for (const auto &kNodePtr : nodes_) {
    if (auto pin = kNodePtr->GetOutputPin(pin_id)) {
      return pin;
    }
  }
  return std::nullopt;
}

auto NodeManager::GetNodes() const
    -> const std::vector<std::unique_ptr<Node>> & {
  return nodes_;
}
