#include <gtest/gtest.h>
#include <dfd_model/DataItem.h>
#include <nlohmann/json.hpp>

TEST(DataItemTest, SerializeDeserializeTest) {
  // Create a DataItem instance with properties.
  auto data_item = std::make_shared<DataItem>(1, "DataItemName", "TypeName");
  data_item->CreateDataDef("Key1", "Value1");
  data_item->CreateDataDef("Key2", "Value2");

  auto sub_data_item = std::make_shared<DataItem>(2, "SubDataItemName", "SubTypeName");
  sub_data_item->CreateDataDef("Key3", "Value3");
  data_item->AddSubDataItem(sub_data_item);

  // Serialize the DataItem instance to a JSON object.
  nlohmann::json json = data_item->Serialize();

  // Deserialize the JSON object back to a new DataItem instance.
  auto deserialized_data_item = DataItem::Deserialize(json);

  // Compare the properties of the original and deserialized DataItem instances.
  EXPECT_EQ(data_item->GetElementId(), deserialized_data_item->GetElementId());
  EXPECT_EQ(data_item->GetName()->get(), deserialized_data_item->GetName()->get());
  EXPECT_EQ(data_item->GetDataDefs(), deserialized_data_item->GetDataDefs());

  const auto &original_sub_data_items = data_item->GetSubDataItems();
  const auto &deserialized_sub_data_items = deserialized_data_item->GetSubDataItems();
  ASSERT_EQ(original_sub_data_items.size(), deserialized_sub_data_items.size());

  for (size_t i = 0; i < original_sub_data_items.size(); ++i) {
    EXPECT_EQ(original_sub_data_items[i]->GetElementId(), deserialized_sub_data_items[i]->GetElementId());
    EXPECT_EQ(original_sub_data_items[i]->GetName()->get(), deserialized_sub_data_items[i]->GetName()->get());
    EXPECT_EQ(original_sub_data_items[i]->GetDataDefs(), deserialized_sub_data_items[i]->GetDataDefs());
  }
}
