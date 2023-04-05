#include <dfd_model/DataProcess.h>
#include <dfd_model/Dfd.h>

DataProcess::DataProcess(const std::string &name, std::pair<float, float> pos)
    : DfdNode(name, pos), process_description_("no description"),
      sub_dfd_(std::make_shared<Dfd>(name + "_dfd")) {
}

DataProcess::DataProcess(
    uint64_t id, const std::string &name, std::pair<float, float> pos)
    : DfdNode(id, name, pos), process_description_("no description"),
      sub_dfd_(std::make_shared<Dfd>(name + "_dfd")) {
}
auto DataProcess::Serialize() const -> nlohmann::json {
  nlohmann::json json = DfdNode::Serialize();

  json["process_description"] = process_description_;

  return json;
}
auto DataProcess::Create(uint64_t id, const std::string &name,
    std::pair<float, float> pos) -> std::shared_ptr<DataProcess> {
  return std::shared_ptr<DataProcess>(new DataProcess(id, name, pos));
}
auto DataProcess::Create(const std::string &name, std::pair<float, float> pos)
    -> std::shared_ptr<DataProcess> {
  return std::shared_ptr<DataProcess>(new DataProcess(name, pos));
}
