set(MODULE_NAME "transducer")

set(MODULE_SOURCES
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

file(GLOB MODULE_HEADERS "*.h")

add_library(levenshtein-${MODULE_NAME} SHARED ${MODULE_SOURCES})

set_target_properties(levenshtein-${MODULE_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

target_link_libraries(levenshtein-${MODULE_NAME} PUBLIC
  levenshtein-collection)

install(TARGETS levenshtein-${MODULE_NAME}
  EXPORT ${PROJECT_NAME}-${MODULE_NAME}
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

install(FILES ${MODULE_HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/${MODULE_NAME})
