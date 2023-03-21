#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_DATAPROCESSDATA_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_DATAPROCESSDATA_H_

#include <string>
#include <vector>

class DataProcessData {
public:
  DataProcessData(std::string *description, int64_t canvas_id)
      : processing_description_(description),
        sub_data_flow_diagram_id_(canvas_id) {
  }

  void AddInputDataFlow(uint64_t node_id) {
    input_data_flows_.push_back(node_id);
  }
  void AddOutputDataFlow(uint64_t node_id) {
    output_data_flows_.push_back(node_id);
  }
  void RemoveInputDataFlow(uint64_t node_id);
  void RemoveOutputDataFlow(uint64_t node_id);

private:
  std::vector<uint64_t> input_data_flows_;
  std::vector<uint64_t> output_data_flows_;
  std::string *processing_description_;
  int64_t sub_data_flow_diagram_id_;

public:
  [[nodiscard]] auto GetInputDataFlows() const
      -> const std::vector<uint64_t> & {
    return input_data_flows_;
  }
  [[nodiscard]] auto GetOutputDataFlows() const
      -> const std::vector<uint64_t> & {
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

  void SetSubDataFlowDiagramId(int64_t canvas_id) {
    sub_data_flow_diagram_id_ = canvas_id;
  }
  [[nodiscard]] auto GetSubDataFlowDiagramId() const -> uint64_t {
    return sub_data_flow_diagram_id_;
  }
};

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_DATAPROCESSDATA_H_
