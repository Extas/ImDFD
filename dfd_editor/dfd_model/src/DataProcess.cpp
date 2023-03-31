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
auto DataProcess::Serialize() const -> std::string {
  std::string base_serialized = DfdNode::Serialize();
  nlohmann::json json = nlohmann::json::parse(base_serialized);

  json["process_description"] = process_description_;

  return json.dump();
}
