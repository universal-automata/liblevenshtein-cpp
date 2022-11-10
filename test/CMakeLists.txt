list(APPEND CMAKE_MODULE_PATH
  /usr/lib/cmake/GTest
  /usr/share/rapidcheck/cmake
  /usr/share/cmake/yaml-cpp)

include(GTestConfig)
include(rapidcheckConfig)
include(yaml-cpp-config)

set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(test-${PROJECT_NAME}
  "test_${PROJECT_NAME}.cpp")

add_test(NAME test-${PROJECT_NAME} COMMAND test-${PROJECT_NAME})

target_link_libraries(test-${PROJECT_NAME} PUBLIC
  levenshtein
  gtest
  rapidcheck_gtest
  yaml-cpp)

target_include_directories(test-${PROJECT_NAME} PUBLIC
  "${SOURCE_DIR}"
  "${TEST_DIR}")

add_subdirectory(liblevenshtein)

file(COPY "${TEST_DIR}/${PROJECT_NAME}/config/rapidcheck.yaml"
  DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
