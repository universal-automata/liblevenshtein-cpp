file(RELATIVE_PATH MODULE_INCLUDE_DIR "${SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB MODULE_HEADERS "*.h" "*.hpp")

target_sources(levenshtein PUBLIC
  ${MODULE_HEADERS}
  "symmetric_pair.cpp"
  "memoized_distance.cpp"
  "standard_distance.cpp"
  "transposition_distance.cpp"
  "merge_and_split_distance.cpp"
  )

install(FILES ${MODULE_HEADERS}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${MODULE_INCLUDE_DIR}")
