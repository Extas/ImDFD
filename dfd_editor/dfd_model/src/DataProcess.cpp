#include <dfd_model/DataProcess.h>
#include <dfd_model/Dfd.h>

DataProcess::DataProcess(std::string name)
    : DfdElement(std::move(name)), process_description_(),
      sub_dfd_(std::make_shared<Dfd>()) {
}
