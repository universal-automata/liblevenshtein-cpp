add_executable(main
  "main.cpp")

target_link_libraries(main
  levenshtein-utils
  levenshtein-collection
  levenshtein-distance)
