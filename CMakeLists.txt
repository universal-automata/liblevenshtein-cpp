cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(liblevenshtein
  VERSION 4.0.0
  DESCRIPTION "A library for generating Finite State Transducers based on Levenshtein Automata."
  HOMEPAGE_URL "https://github.com/universal-automata/liblevenshtein-cpp"
  LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
SET(CMAKE_C_FLAGS_DEBUG "-g -O0")

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

include(GNUInstallDirs)

option(BUILD_BASELINE_METRICS "Builds baseline distance metrics for validation" ON)
option(BUILD_TESTS "Build liblevenshtein testing suite" OFF)
option(ENABLE_TEST_COVERAGE "Generate test coverage report" OFF)
option(ENABLE_LINTING "Enables the source code linter" OFF)

if(ENABLE_LINTING)
  find_program(CLANGXX_PATH clang++)
  find_program(CLANG_TIDY_PATH clang-tidy)
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  set(CMAKE_CXX_COMPILER "${CLANGXX_PATH}")
  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_PATH}")
endif()

if(NOT BUILD_BASELINE_METRICS AND BUILD_TESTS)
  message(WARNING "Building baseline metrics because they are required by the tests.")
  SET(BUILD_BASELINE_METRICS ON)
endif()

add_subdirectory(proto)
add_subdirectory(third-party)
add_subdirectory(src)

set_target_properties(levenshtein PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

install(TARGETS levenshtein
  EXPORT "${PROJECT_NAME}-targets"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

install(EXPORT "${PROJECT_NAME}-targets"
  FILE "${PROJECT_NAME}-targets.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
  VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

if(BUILD_TESTS)
  add_subdirectory(test)
endif()
