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
option(BUILD_TESTS "Build liblevenshtein testing suite" ON)
option(ENABLE_TEST_COVERAGE "Generate test coverage report" OFF)

if(NOT BUILD_BASELINE_METRICS AND BUILD_TESTS)
  message(WARNING "Building baseline metrics because they are required by the tests.")
  SET(BUILD_BASELINE_METRICS ON)
endif()

add_subdirectory(proto)
add_subdirectory(src)

set_target_properties(levenshtein PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

install(TARGETS levenshtein
  EXPORT "${PROJECT_NAME}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

if(BUILD_TESTS)
  add_subdirectory(test)
endif()
