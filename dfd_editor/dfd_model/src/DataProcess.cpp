#include <dfd_model/DataProcess.h>
#include <dfd_model/Dfd.h>
#include <utility>

DataProcess::DataProcess(const std::string &name, std::pair<float, float> pos)
    : DfdNode(name, pos, "nod"),
      sub_dfd_(std::make_shared<Dfd>(name + "_dfd")) {
}

DataProcess::DataProcess(
    uint64_t id, const std::string &name, std::pair<float, float> pos)
    : DfdNode(id, name, pos, "nod"),
      sub_dfd_(std::make_shared<Dfd>(name + "_dfd")) {
}
auto DataProcess::Serialize() const -> nlohmann::json {
  nlohmann::json json = DfdNode::Serialize("DataProcess");

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

auto DataProcess::DeSerialize(nlohmann::json json)
    -> std::shared_ptr<DataProcess> {
  auto id = json["id"].get<uint64_t>();
  auto name = json["name"].get<std::string>();
  auto pos = json["pos"].get<std::pair<float, float>>();

  auto data_process = Create(id, name, pos);

  return data_process;
}
