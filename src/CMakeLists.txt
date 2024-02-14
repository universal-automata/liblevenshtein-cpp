set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(levenshtein PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
  "$<INSTALL_INTERFACE:include>")

add_subdirectory(liblevenshtein)
