#ifndef IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_INFOWINDOW_H_
#define IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_INFOWINDOW_H_

#include "DataItemPopup.h"
#include "logging/Logger.h"
#include <dfd_model/DataFlow.h>
#include <dfd_model/DataItem.h>
#include <dfd_model/DataProcess.h>
#include <dfd_model/DataStorage.h>
#include <dfd_model/Dfd.h>
#include <dfd_model/DfdNode.h>
#include <dfd_model/Element.h>
#include <dfd_model/ExternalEntity.h>
#include <imgui.h>
#include <signal/SignalHandel.h>
#include <ui/BaseWindow.h>

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

class Info {
public:
  Info() = default;

  void LoadNode(const std::shared_ptr<DfdNode> &node);

  void LoadLink(const std::shared_ptr<DataFlow> &link);

  void LoadElement(const std::shared_ptr<Element> &element);

  [[nodiscard]] auto GetName()
      -> std::optional<std::reference_wrapper<std::string>>;

  [[nodiscard]] auto GetDescription()
      -> std::optional<std::reference_wrapper<std::string>>;

  [[nodiscard]] auto GetDataItems() -> std::vector<std::shared_ptr<DataItem>> &;

  [[nodiscard]] auto GetElement() -> std::shared_ptr<Element>;
  private:
  std::unordered_map<std::string, bool> editing_;

  std::optional<std::reference_wrapper<std::string>> name_;
  std::optional<std::reference_wrapper<std::string>> description_;
  std::vector<std::shared_ptr<DataItem>> data_items_;
  std::shared_ptr<Element> current_element_;
};

class InfoWindow : public BaseWindow {
public:
  explicit InfoWindow();

  void DrawContents() override;

  static auto DrawTextValue(const std::optional<std::string> &text,
      const std::string &label = "") -> bool;

  static void DrawEditableTextValue(
      std::optional<std::reference_wrapper<std::string>> text,
      const std::string &label = "");

  void DrawDataItems(std::vector<std::shared_ptr<DataItem>> &items);

  static void DrawDataTypeSelector(std::shared_ptr<DataItem> data_item);

  void LoadDfd(const std::shared_ptr<Dfd> &dfd);

private:
  std::shared_ptr<Dfd> dfd_;
  Info info_;

  inline static DataItemPopup data_item_popup_;
};

#endif // IMDFD_DFD_EDITOR_INCLUDE_DFD_EDITOR_INFOWINDOW_H_
