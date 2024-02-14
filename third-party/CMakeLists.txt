file(GLOB MODULE_HEADERS "*.h" "*.hpp")

target_include_directories(levenshtein PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
  "$<INSTALL_INTERFACE:include>")

target_sources(levenshtein
  PRIVATE
    "MurmurHash2.cpp"
    "MurmurHash3.cpp")

install(FILES ${MODULE_HEADERS}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
