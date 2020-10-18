set(MODULE_NAME "distance")

set(MODULE_SOURCES
  "symmetric_pair.cpp"
  "memoized_distance.cpp"
  "standard_distance.cpp"
  "transposition_distance.cpp"
  "merge_and_split_distance.cpp")

file(GLOB MODULE_HEADERS "*.h")

add_library(levenshtein-${MODULE_NAME} SHARED ${MODULE_SOURCES})

target_include_directories(levenshtein-${MODULE_NAME} PUBLIC "${SOURCE_ROOT}")

set_target_properties(levenshtein-${MODULE_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

install(TARGETS levenshtein-${MODULE_NAME}
  EXPORT ${PROJECT_NAME}-${MODULE_NAME}
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

install(FILES ${MODULE_HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/${MODULE_NAME})
