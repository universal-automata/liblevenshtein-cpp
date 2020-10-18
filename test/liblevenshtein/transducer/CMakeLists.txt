set(MODULE_NAME "transducer")

set(TEST_SOURCES
  "test_helpers.cpp"
  "test_comparator.cpp"
  "test_state.cpp"
  "test_merge.cpp"
  "test_transducer.cpp"
  "test_module.cpp")

add_executable(test-${MODULE_NAME} ${TEST_SOURCES})
add_test(NAME test-${MODULE_NAME} COMMAND test-${MODULE_NAME})
target_link_libraries(test-${MODULE_NAME} PUBLIC
  levenshtein-rapidcheck-parser
  levenshtein-collection
  levenshtein-distance
  levenshtein-${MODULE_NAME}
  gtest
  rapidcheck_gtest)

target_include_directories(test-${MODULE_NAME} PUBLIC
  "${SOURCE_ROOT}"
  "${TEST_ROOT}")

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rapidcheck.yaml")
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/rapidcheck.yaml"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
else()
  file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../config/rapidcheck.yaml"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
endif()
