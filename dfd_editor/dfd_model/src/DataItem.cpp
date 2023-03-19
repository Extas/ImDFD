#include <dfd_model/DataItem.h>

DataItem::DataItem(std::string name, DataType data_type)
    : Element(), name_(std::move(name)), data_type_(data_type) {
}

auto DataItem::Serialize() const -> std::string {
  return {};
}
auto DataItem::IsValid() const -> bool {
  return true;
}
