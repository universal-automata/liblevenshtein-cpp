file(RELATIVE_PATH MODULE_INCLUDE_DIR "${SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB MODULE_HEADERS "*.h" "*.hpp")

target_sources(levenshtein PUBLIC
  ${MODULE_HEADERS}
  "position.cpp"
  "state.cpp"
  "state_iterator.cpp"
  "subsumes.cpp"
  "unsubsume.cpp"
  "distance.cpp"
  "merge.cpp"
  "intersection.cpp"
  "comparator.cpp"
  "position_transition.cpp"
  "state_transition.cpp"
  "lazy_query.cpp"
  "transducer.cpp"
  )

install(FILES ${MODULE_HEADERS}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${MODULE_INCLUDE_DIR}")
