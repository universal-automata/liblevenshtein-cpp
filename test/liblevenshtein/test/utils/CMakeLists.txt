file(GLOB MODULE_HEADERS "*.h" "*.hpp")

target_sources(test-${PROJECT_NAME} PUBLIC
  ${MODULE_HEADERS}
  "comparators.cpp"
  "file_utils.cpp"
  "position_utils.cpp"
  "test_comparators.cpp"
  )
