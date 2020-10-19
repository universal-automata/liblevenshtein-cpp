file(RELATIVE_PATH MODULE_INCLUDE_DIR "${TEST_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB MODULE_HEADERS "*.h" "*.hpp")

target_sources(test-${PROJECT_NAME} PUBLIC
  ${MODULE_HEADERS}
  "test_symmetric_pair.cpp"
  "test_standard_distance.cpp"
  "test_transposition_distance.cpp"
  "test_merge_and_split_distance.cpp"
  )
