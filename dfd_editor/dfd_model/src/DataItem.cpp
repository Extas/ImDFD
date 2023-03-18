#include <dfd_model/DataItem.h>

DataItem::DataItem(std::string name, DataType data_type)
    : name_(std::move(name)), data_type_(data_type) {
}

auto DataItem::serialize() const -> std::string {
  return {};
}
auto DataItem::is_valid() const -> bool {
  return true;
}
