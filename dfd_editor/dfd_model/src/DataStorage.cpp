#include <dfd_model/DataStorage.h>

#include <utility>
DataStorage::DataStorage(std::string name, std::pair<float, float> pos)
    : DfdNode(std::move(name), pos) {
}
