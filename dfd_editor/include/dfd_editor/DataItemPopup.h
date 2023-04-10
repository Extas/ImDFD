#ifndef IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_DATAITEMPOPUP_H_
#define IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_DATAITEMPOPUP_H_

#include <dfd_model/DataItem.h>
#include <ui/BasePopup.h>

class DataItemPopup : public BasePopup {
public:
  DataItemPopup();
  void DrawContents() override;
  void Draw() override;

  void LoadDataItems(std::vector<std::shared_ptr<DataItem>> &data_items);
private:
  std::vector<std::shared_ptr<DataItem>> *data_items_{};
  void DrawDataItems();
  void DrawDataItem(std::shared_ptr<DataItem>);
  void DrawAddDataItemButton();
};

#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_DATAITEMPOPUP_H_
