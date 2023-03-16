#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_DATAPROCESS_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_DATAPROCESS_H_

#include <string>
#include <vector>

class DataProcess {
public:
  DataProcess(std::string name, std::string description)
      : name_(std::move(name)), description_(std::move(description)) {
  }

  DataProcess() : name_("DataProcess"), description_("") {
  }

  void AddInputDataFlow(int id) {
    input_data_flows_.push_back(id);
  }
  void RemoveInputDataFlow(int id);

  void AddOutputDataFlow(int id) {
    output_data_flows_.push_back(id);
  }
  void RemoveOutputDataFlow(int id);

private:
  std::string name_;
  std::string description_;
  std::vector<int> input_data_flows_;
  std::vector<int> output_data_flows_;
  int sub_data_flow_diagram_id_;

public:
  const std::string &GetName() const {
    return name_;
  }
  void SetName(const std::string &name) {
    name_ = name;
  }
  const std::string &GetDescription() const {
    return description_;
  }
  void SetDescription(const std::string &description) {
    description_ = description;
  }

  const std::vector<int> &GetInputDataFlows() const {
    return input_data_flows_;
  }
  const std::vector<int> &GetOutputDataFlows() const {
    return output_data_flows_;
  }
  void SetSubDataFlowDiagramId(int id) {
    sub_data_flow_diagram_id_ = id;
  }
  int GetSubDataFlowDiagramId() const {
    return sub_data_flow_diagram_id_;
  }
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_DATAPROCESS_H_
