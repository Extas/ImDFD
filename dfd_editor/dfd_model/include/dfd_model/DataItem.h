
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAITEM_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAITEM_H_

#include "Element.h"
#include "data_type/DataType.h"

#include <memory>
#include <vector>

class DataItem : public Element {
public:
  DataItem(std::string name, DataType data_type);

  std::string name_;
  DataType data_type_;
  std::vector<std::shared_ptr<DataItem>> sub_data_items_;

  [[nodiscard]] auto Serialize() const -> std::string override;
  [[nodiscard]] auto IsValid() const -> bool override;
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DATAITEM_H_