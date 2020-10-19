cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(liblevenshtein
  VERSION 4.0.0
  DESCRIPTION "A library for generating Finite State Transducers based on Levenshtein Automata."
  HOMEPAGE_URL "https://github.com/universal-automata/liblevenshtein-cpp"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

include(GNUInstallDirs)

option(BUILD_BASELINE_METRICS "Builds baseline distance metrics for validation" ON)
option(BUILD_TESTS "Build liblevenshtein testing suite" ON)

if(NOT BUILD_BASELINE_METRICS AND BUILD_TESTS)
  message(WARNING "Building baseline metrics because they are required by the tests.")
  SET(BUILD_BASELINE_METRICS ON)
endif()

add_subdirectory(src)

if(BUILD_TESTS)
  add_subdirectory(test)
endif()
