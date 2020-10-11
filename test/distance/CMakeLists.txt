set(MODULE_NAME "distance")

set(TEST_SOURCES
  "test_standard_distance.cpp"
  "test_transposition_distance.cpp"
  "test_merge_and_split_distance.cpp"
  "test_${MODULE_NAME}.cpp")

add_executable(test-${MODULE_NAME} ${TEST_SOURCES})
add_test(NAME test-${MODULE_NAME} COMMAND test-${MODULE_NAME})
target_link_libraries(test-${MODULE_NAME} PUBLIC
  levenshtein-utils
  levenshtein-collection
  levenshtein-${MODULE_NAME}
  gtest
  rapidcheck_gtest)
