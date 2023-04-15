#ifndef IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_DATAITEMPOPUP_H_
#define IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_DATAITEMPOPUP_H_

#include <dfd_model/DataItem.h>
#include <dfd_model/DataStorage.h>
#include <dfd_model/Element.h>
#include <stdint.h>
#include <ui/BasePopup.h>

class DataItemPopup : public BasePopup {
public:
  DataItemPopup();
  void DrawContents() override;
  void Draw() override;

  void SetData(std::shared_ptr<Element> element, uint64_t data_item_id);

private:
  std::shared_ptr<Element> element_{};
  uint64_t data_item_id_;
  void DrawDataItem(const std::shared_ptr<DataItem> &);
};

#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_DATAITEMPOPUP_H_
