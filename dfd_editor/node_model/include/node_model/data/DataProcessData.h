#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_DATAPROCESSDATA_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_DATAPROCESSDATA_H_

#include <string>
#include <vector>

class DataProcessData {
public:
  DataProcessData(std::string *description, int canvas_id)
      : processing_description_(description),
        sub_data_flow_diagram_id_(canvas_id) {
  }

  void AddInputDataFlow(int node_id) {
    input_data_flows_.push_back(node_id);
  }
  void AddOutputDataFlow(int node_id) {
    output_data_flows_.push_back(node_id);
  }
  void RemoveInputDataFlow(int node_id);
  void RemoveOutputDataFlow(int node_id);

private:
  std::vector<int> input_data_flows_;
  std::vector<int> output_data_flows_;
  std::string *processing_description_;
  int sub_data_flow_diagram_id_;

public:
  [[nodiscard]] auto GetInputDataFlows() const -> const std::vector<int> & {
    return input_data_flows_;
  }
  [[nodiscard]] auto GetOutputDataFlows() const -> const std::vector<int> & {
    return output_data_flows_;
  }

  [[nodiscard]] auto GetDescription() const -> const std::string & {
    return *processing_description_;
  }
  [[nodiscard]] auto GetDescriptionPtr() const -> std::string * {
    return processing_description_;
  }
  void SetContent(const std::string &content) const {
    *processing_description_ = content;
  }

  void SetSubDataFlowDiagramId(int canvas_id) {
    sub_data_flow_diagram_id_ = canvas_id;
  }
  [[nodiscard]] auto GetSubDataFlowDiagramId() const -> int {
    return sub_data_flow_diagram_id_;
  }
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_DATAPROCESSDATA_H_
