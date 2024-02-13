file(GLOB MODULE_HEADERS "*.h" "*.hpp")

target_sources(test-${PROJECT_NAME} PUBLIC
  ${MODULE_HEADERS}
  )

add_subdirectory(utils)
