file(RELATIVE_PATH MODULE_INCLUDE_DIR "${TEST_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB MODULE_HEADERS "*.h" "*.hpp")

target_sources(test-${PROJECT_NAME} PUBLIC
  ${MODULE_HEADERS}
  "test_dawg_node.cpp"
  "test_prefix.cpp"
  "test_transition.cpp"
  "test_sorted_dawg.cpp"
  )
