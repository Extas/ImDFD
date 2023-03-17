#ifndef IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_DATAPROCESSDATA_H_
#define IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_DATAPROCESSDATA_H_

#include <string>
#include <vector>

class DataProcessData {
public:
  explicit DataProcessData(int canvas_id)
      : processing_content_("no description"),
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
  std::string processing_content_;
  std::vector<int> input_data_flows_;
  std::vector<int> output_data_flows_;
  int sub_data_flow_diagram_id_;

public:
  [[nodiscard]] auto GetInputDataFlows() const -> const std::vector<int> & {
    return input_data_flows_;
  }
  [[nodiscard]] auto GetOutputDataFlows() const -> const std::vector<int> & {
    return output_data_flows_;
  }

  [[nodiscard]] auto GetContent() const -> const std::string & {
    return processing_content_;
  }
  void SetContent(const std::string &content) {
    processing_content_ = content;
  }

  void SetSubDataFlowDiagramId(int canvas_id) {
    sub_data_flow_diagram_id_ = canvas_id;
  }
  [[nodiscard]] auto GetSubDataFlowDiagramId() const -> int {
    return sub_data_flow_diagram_id_;
  }
};

// void DataProcessData::RemoveOutputDataFlow(int node_id) {
//   for (auto it = output_data_flows_.begin(); it != output_data_flows_.end();
//        ++it) {
//     if (*it == node_id) {
//       output_data_flows_.erase(it);
//       break;
//     }
//   }
// }
// void DataProcessData::RemoveInputDataFlow(int node_id) {
//   for (auto it = input_data_flows_.begin(); it != input_data_flows_.end();
//        ++it) {
//     if (*it == node_id) {
//       input_data_flows_.erase(it);
//       break;
//     }
//   }
// }

#endif // IMDFD_DFD_EDITOR_NODE_MODEL_INCLUDE_NODE_MODEL_DATA_DATAPROCESSDATA_H_
