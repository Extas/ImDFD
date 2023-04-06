#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFD_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFD_H_

#include "Element.h"

#include "DataFlow.h"
#include "DataItem.h"
#include "DataProcess.h"
#include "DataStorage.h"
#include "ExternalEntity.h"
#include "dfd_model/DfdNode.h"

class Dfd : public Element {
public:
  explicit Dfd(std::string name);
  Dfd(uint64_t id, std::string name);
  std::vector<std::shared_ptr<DataFlow>> data_flows_;
  std::vector<std::shared_ptr<DataItem>> data_items_;
  std::vector<std::shared_ptr<DataProcess>> data_processes_;
  std::vector<std::shared_ptr<ExternalEntity>> external_entities_;
  std::vector<std::shared_ptr<DataStorage>> data_storages_;

  auto AddNode(const std::string &node_type, const std::pair<float, float> &pos,
      const std::string &name = "") -> uint64_t;
  auto DeleteNode(uint64_t node_id) -> bool {
    DfdNode *to_delete = nullptr;
    auto iter = std::find_if(data_processes_.begin(), data_processes_.end(),
        [node_id](
            const auto &node) { return node->GetElementId() == node_id; });
    if (iter != data_processes_.end()) {
      auto data_process = *iter;
      data_processes_.erase(iter);
      to_delete = data_process.get();
    }

    auto iter2 = std::find_if(data_storages_.begin(), data_storages_.end(),
        [node_id](
            const auto &node) { return node->GetElementId() == node_id; });
    if (iter2 != data_storages_.end()) {
      auto data_storage = *iter2;
      data_storages_.erase(iter2);
      to_delete = data_storage.get();
    }

    auto iter3 = std::find_if(external_entities_.begin(),
        external_entities_.end(), [node_id](const auto &node) {
          return node->GetElementId() == node_id;
        });

    if (iter3 != external_entities_.end()) {
      auto external_entity = *iter3;
      external_entities_.erase(iter3);
      to_delete = external_entity.get();
    }

    if (to_delete == nullptr) {
      return false;
    }

    // delete all flows connected to this node,use flow.HasNode(node_id) to check
    data_flows_.erase(std::remove_if(data_flows_.begin(), data_flows_.end(),
        [node_id](const auto &flow) { return flow->HasNode(node_id); }),
        data_flows_.end());

    return true;
  }

  auto AddDataFlow(const std::string &name, uint64_t src_node_id,
      uint64_t dst_node_id) -> uint64_t;
  auto DeleteFlow(uint64_t flow_id) -> bool;

  void CreateTestData();

  [[nodiscard]] auto GetJsonString() const -> std::string;

  [[nodiscard]] auto Serialize() const -> nlohmann::json override;

  [[nodiscard]] auto IsValid() const -> bool override;

  [[nodiscard]] auto GetName() const -> std::string;

private:
  std::string name_;

  auto CreateDataProcessNode(const std::string &name,
      const std::pair<float, float> &pos) -> std::shared_ptr<DataProcess>;
  auto CreateDataStorageNode(const std::string &name,
      const std::pair<float, float> &pos) -> std::shared_ptr<DataStorage>;
  auto CreateExternalEntityNode(const std::string &name,
      const std::pair<float, float> &pos) -> std::shared_ptr<ExternalEntity>;
  auto CreateDataFlow(const std::string &name,
      const std::shared_ptr<DfdNode> &src, const std::shared_ptr<DfdNode> &dst,
      const std::pair<float, float> &pos) -> std::shared_ptr<DataFlow>;

  auto FindNodeById(uint64_t node_id) -> std::shared_ptr<DfdNode>;
};
#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFD_H_
