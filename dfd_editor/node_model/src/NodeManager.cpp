#include <functional>
#include <node_model/DataStorageNode.h>
#include <node_model/ExternalEntityNode.h>
#include <node_model/NodeManager.h>

class Dfd;

void NodeManager::AddNode(
    std::string *name, std::pair<float, float> *position) {
  nodes_.push_back(std::make_unique<Node>(name, position));
}
void NodeManager::AddNode(std::string *name) {
  AddNode(name, new std::pair<float, float>(0, 0));
}

void NodeManager::AddDataProcessNode(std::string *name,
    std::pair<float, float> *position, std::string *description,
    const std::shared_ptr<Dfd> &sub_dfd) {

  int get_canvas_id = -1;
  SignalHandel::Instance().create_new_dfd_(sub_dfd, get_canvas_id);

  nodes_.push_back(std::make_unique<DataProcessNode>(
      name, position, description, get_canvas_id));
}
void NodeManager::AddExternalEntityNode(
    std::string *name, std::pair<float, float> *position) {
  nodes_.push_back(std::make_unique<ExternalEntityNode>(name, position));
}
void NodeManager::AddDataStorageNode(
    std::string *name, std::pair<float, float> *position) {
  nodes_.push_back(std::make_unique<DataStorageNode>(name, position));
}

void NodeManager::AddInputPin(std::string *name) {
  nodes_.back()->AddInputPin(name);
}
void NodeManager::AddInputPin(std::string *name, int node_id) {
  if (auto node = GetNode(node_id)) {
    if (node.has_value()) {
      node->get().AddInputPin(name);
    }
  }
}
void NodeManager::AddOutputPin(std::string *name) {
  nodes_.back()->AddOutputPin(name);
}
void NodeManager::AddOutputPin(std::string *name, int node_id) {
  if (auto node = GetNode(node_id)) {
    if (node.has_value()) {
      node->get().AddOutputPin(name);
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

auto NodeManager::GetNodes() const
    -> const std::vector<std::unique_ptr<Node>> & {
  return nodes_;
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
