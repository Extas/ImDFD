#include <dfd_model/DataProcess.h>
#include <dfd_model/Dfd.h>

DataProcess::DataProcess(std::string name, std::pair<float, float> pos)
    : DfdNode(std::move(name), pos), process_description_("no description"),
      sub_dfd_(std::make_shared<Dfd>(name + "_dfd")) {
}
