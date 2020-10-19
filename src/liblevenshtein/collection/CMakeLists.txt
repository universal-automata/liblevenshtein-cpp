file(RELATIVE_PATH MODULE_INCLUDE_DIR "${SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB MODULE_HEADERS "*.h" "*.hpp")

target_sources(levenshtein PUBLIC
  ${MODULE_HEADERS}
  "dawg_node.cpp"
  "prefix.cpp"
  "transition.cpp"
  "dawg.cpp"
  "sorted_dawg.cpp"
  "dawg_iterator.cpp"
  )

install(FILES ${MODULE_HEADERS}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${MODULE_INCLUDE_DIR}")
