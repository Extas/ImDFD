#include <gtest/gtest.h>


// Automatically generates a main() function for running all the tests
GTEST_API_ int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
