#include <gtest/gtest.h>
#include <dfd_model/DataItem.h>

TEST(DataItemTest, SerializeTest) {
  // Set up the DataItem object
  auto data_item = DataItem::CreateStringDataItem("DataItem1", "string");

  nlohmann::json actual_json = data_item->Serialize();

  nlohmann::json expected_json;
  expected_json["id"] = data_item->GetElementId();
  expected_json["name"] = "DataItem1";
  expected_json["data_type"]["type"] = "String";
  expected_json["data_type"]["fmt"] = "string";

  // Compare the actual and expected nlohmann::json objects
  EXPECT_EQ(actual_json, expected_json);
}
