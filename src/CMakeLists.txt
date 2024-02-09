set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(levenshtein PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

add_subdirectory(liblevenshtein)

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
