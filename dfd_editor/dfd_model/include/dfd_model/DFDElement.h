
#ifndef IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFDELEMENT_H_
#define IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFDELEMENT_H_

#include "Serializable.h"

#include <memory>
#include <vector>

class DataFlow;

class DFDElement : public Serializable {
  std::string name;
  std::vector<std::shared_ptr<DataFlow>> input_data_flows;
  std::vector<std::shared_ptr<DataFlow>> output_data_flows;
  // ... 其他方法
};

#endif // IMDFD_DFD_EDITOR_DFD_MODEL_INCLUDE_DFD_MODEL_DFDELEMENT_H_
