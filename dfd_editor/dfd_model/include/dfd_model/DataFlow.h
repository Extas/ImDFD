
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAFLOW_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAFLOW_H_

#include "DataItem.h"
#include "Element.h"

#include <memory>
#include <vector>

class DfdNode;

class DataFlow : public Element {
public:
  DataFlow(std::string name, const std::shared_ptr<DfdNode> &source,
      const std::shared_ptr<DfdNode> &destination, std::pair<float, float> pos);

  std::string name_;
  std::vector<std::shared_ptr<DataItem>> data_items_;
  std::shared_ptr<DfdNode> source_;
  std::shared_ptr<DfdNode> destination_;

  [[nodiscard]] auto Serialize() const -> std::string override;
  [[nodiscard]] auto IsValid() const -> bool override;
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAFLOW_H_
