add_library(${CMAKE_PROJECT_NAME}-distance SHARED
  "memoized_distance.cpp"
  "standard_distance.cpp"
  "transposition_distance.cpp"
  "merge_and_split_distance.cpp")
