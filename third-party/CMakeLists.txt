file(GLOB MODULE_HEADERS "*.h" "*.hpp")

target_include_directories(levenshtein PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

target_sources(levenshtein PUBLIC
  ${MODULE_HEADERS}
  "MurmurHash2.cpp"
  "MurmurHash3.cpp"
)

install(FILES ${MODULE_HEADERS}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
