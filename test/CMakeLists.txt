enable_testing()
find_package(GTest REQUIRED)
find_package(rapidcheck REQUIRED)
find_package(yaml-cpp REQUIRED)

set(TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(test-${PROJECT_NAME}
  "test_${PROJECT_NAME}.cpp")

add_test(NAME test-${PROJECT_NAME} COMMAND test-${PROJECT_NAME})

target_link_libraries(test-${PROJECT_NAME} PUBLIC
  levenshtein
  GTest::gtest_main
  rapidcheck_gtest
  yaml-cpp::yaml-cpp)

target_include_directories(test-${PROJECT_NAME} PUBLIC
  "${SOURCE_DIR}"
  "${TEST_DIR}")

add_subdirectory(liblevenshtein)

file(COPY "${TEST_DIR}/${PROJECT_NAME}/config/rapidcheck.yaml"
  DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

if(ENABLE_TEST_COVERAGE)
  include(CodeCoverage)
  append_coverage_compiler_flags_to_target(levenshtein)
  append_coverage_compiler_flags_to_target(test-${PROJECT_NAME})

  set(LCOV_EXCLUDES
    "${CMAKE_SOURCE_DIR}/src/liblevenshtein/utils/MurmurHash*"
    "${CMAKE_SOURCE_DIR}/test/*"
    "${CMAKE_BINARY_DIR}/generated/liblevenshtein/proto/*"
    "${CMAKE_CXX_COMPILER_VERSION}/*"
  )

  if(DEFINED ENV{CONDA_PREFIX})
    list(APPEND LCOV_EXCLUDES "$ENV{CONDA_PREFIX}/*")
  endif()

  setup_target_for_coverage_lcov(
    NAME coverage
    BASE_DIRECTORY test
    EXECUTABLE test-liblevenshtein
    EXCLUDE ${LCOV_EXCLUDES})
endif()
