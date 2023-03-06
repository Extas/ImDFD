# ====================================================
# Build instructions
# ====================================================

set(MAIN_TEST_TARGET_NAME ${MODULE_TARGET_NAME}_test)

asap_add_test(
  ${MAIN_TEST_TARGET_NAME}
  UNIT_TEST
  VALGRIND_MEMCHECK
  SRCS
  "main.cpp"
  LINK
  ${MODULE_TARGET_NAME}
  gtest
  gmock
  COMMENT
  "logging unit tests")

asap_set_language_standards(${MAIN_TEST_TARGET_NAME} CXX 17)

gtest_discover_tests(${MAIN_TEST_TARGET_NAME})

# Add support for (optional) code quality tools
asap_add_sanitizers(${MAIN_TEST_TARGET_NAME})
swift_add_valgrind_massif(${MAIN_TEST_TARGET_NAME})
swift_add_valgrind_callgrind(${MAIN_TEST_TARGET_NAME})
