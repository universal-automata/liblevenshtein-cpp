cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

project(liblevenshtein-demo
  VERSION 1.0.0
  DESCRIPTION "Demonstrates how to use liblevenshtein-cpp."
  HOMEPAGE_URL "https://github.com/universal-automata/liblevenshtein-cpp"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
SET(CMAKE_C_FLAGS_DEBUG "-g -O0")

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

include(GNUInstallDirs)

find_package(absl REQUIRED) # workaround for protobuf linking bug
find_package(Protobuf REQUIRED)
find_package(liblevenshtein REQUIRED)

add_executable(${PROJECT_NAME}
  "command_line.cpp"
  "main.cpp")

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    absl::log_internal_check_op # workaround for protobuf linking bug
    protobuf::libprotobuf
    levenshtein)
