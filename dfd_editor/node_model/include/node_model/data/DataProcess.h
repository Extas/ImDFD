#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_DATAPROCESS_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_DATAPROCESS_H_

#include <string>
#include <vector>

class DataProcess {
public:
  DataProcess(std::string description)
      : processing_content_(std::move(description)) {
  }

  DataProcess() : DataProcess("no description") {
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
  std::string processing_content_;
  std::vector<int> input_data_flows_;
  std::vector<int> output_data_flows_;
  int sub_data_flow_diagram_id_;

public:
  const std::string &GetContent() const {
    return processing_content_;
  }
  void SetContent(const std::string &content) {
    processing_content_ = content;
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
