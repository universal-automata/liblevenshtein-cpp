file(RELATIVE_PATH MODULE_INCLUDE_DIR "${TEST_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB MODULE_HEADERS "*.h" "*.hpp")

target_sources(test-${PROJECT_NAME} PUBLIC
  ${MODULE_HEADERS}
  "test_state.cpp"
  "test_merge.cpp"
  "test_transducer.cpp"
  )
