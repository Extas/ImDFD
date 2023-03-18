
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAFLOW_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAFLOW_H_

#include "DataItem.h"
#include "Serializable.h"

#include <memory>
#include <vector>

class DfdElement;

class DataFlow : public Serializable {
public:
  DataFlow(std::string name, const std::shared_ptr<DfdElement> &source,
      const std::shared_ptr<DfdElement> &destination);

  std::string name_;
  std::vector<std::shared_ptr<DataItem>> data_items_;
  std::shared_ptr<DfdElement> source_;
  std::shared_ptr<DfdElement> destination_;

  [[nodiscard]] auto serialize() const -> std::string override;
  [[nodiscard]] auto is_valid() const -> bool override;
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAFLOW_H_
