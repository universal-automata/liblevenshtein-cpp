set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(levenshtein SHARED "")
target_include_directories(levenshtein PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

add_subdirectory(liblevenshtein)

set_target_properties(levenshtein PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

install(TARGETS levenshtein
  EXPORT "${PROJECT_NAME}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

# FIXME: The following seems to be broken for now.

# include(CMakePackageConfigHelpers)

# write_basic_package_version_file(
#   "${PROJECT_NAME}-config-version.cmake"
#   VERSION "${PACKAGE_VERSION}"
#   COMPATIBILITY SameMajorVersion)

# install(EXPORT "${PROJECT_NAME}"
#   FILE "${PROJECT_NAME}.cmake"
#   NAMESPACE liblevenshtein::
#   DESTINATION "lib/cmake/${PROJECT_NAME}")
