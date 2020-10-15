# set(MODULE_NAME "utils")

# set(TEST_SOURCES
#   "test_module.cpp")

# add_executable(test-${MODULE_NAME} ${TEST_SOURCES})
# add_test(NAME test-${MODULE_NAME} COMMAND test-${MODULE_NAME})
# target_link_libraries(test-${MODULE_NAME} PUBLIC
#   levenshtein-rapidcheck-parser
#   levenshtein-${MODULE_NAME}
#   gtest)

# if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/rapidcheck.yaml")
#   file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/rapidcheck.yaml"
#     DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
# else()
#   file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../config/rapidcheck.yaml"
#     DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
# endif()
