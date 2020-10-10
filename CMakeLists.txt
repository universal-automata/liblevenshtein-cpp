cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(levenshtein
  VERSION 4.0.0
  DESCRIPTION "A library for generating Finite State Transducers based on Levenshtein Automata."
  HOMEPAGE_URL "https://github.com/universal-automata/liblevenshtein-cpp"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

add_subdirectory(src)
add_subdirectory(test)
