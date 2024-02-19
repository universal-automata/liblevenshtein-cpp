# liblevenshtein-cpp

| Action Type | Build Status |||
|        ---: |    :---:     | :---: | :---: |
| **Operating System** | [![Test Ubuntu](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/test-ubuntu.yml/badge.svg)](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/test-ubuntu.yml) | [![Test MacOS](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/test-macos.yml/badge.svg)](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/test-macos.yml) | [![Test Windows](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/test-windows.yml/badge.svg)](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/test-windows.yml) |
| **Engineering Excellence** | [![Coverage Status](https://coveralls.io/repos/github/universal-automata/liblevenshtein-cpp/badge.svg?branch=master)](https://coveralls.io/github/universal-automata/liblevenshtein-cpp?branch=master) | [![Linter](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/linter.yml/badge.svg)](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/linter.yml) | [![CodeQL](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/codeql.yml/badge.svg)](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/codeql.yml) |
| **Demo App** | [![Run Demo](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/run-demo.yml/badge.svg)](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/run-demo.yml) |||
| **Documentation** | [![Deploy static content to Pages](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/deploy-static-pages.yml/badge.svg)](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/deploy-static-pages.yml) |||

A library for generating Finite State Transducers based on Levenshtein Automata.

NOTE: This library is currently in rc phase. I'll have it production ready as
soon as possible. Currently, there is >90% test coverage over the sources and
the library is usable as described below.

Due to limited resources on my part, this library requires C++20 features (or
whichever is the latest standard). If you need compatibility with an older
standard, please either submit a pull request (preferably) or create an issue
stating the standard you need compatibility with and I will comply if I can.

For a demonstration, please reference the [example app](example/README.md).

For API documentation, please reference the
[GitHub Pages](https://universal-automata.github.io/liblevenshtein-cpp/).

## Development and Installation

For instructions how to develop and install liblevenshtein, please reference the
[wiki](https://github.com/universal-automata/liblevenshtein-cpp/wiki/Development).

## Usage

### Algorithms

`liblevenshtein` supports three variations of Levenshtein distance, where each
variation is defined by the elementary operations it supports. An elementary
operation is an edit operation that errs in a penalty of 1 unit.

1. `liblevenshtein::Algorithm::STANDARD`
  * Standard Levenshtein distance including the traditional elementary
    operations of `insert`, `delete`, and `substitute`.
2. `liblevenshtein::Algorithm::TRANSPOSITION`
  * Standard Levenshtein distance extended with `transpose` as an elementary
    operation.
  * The elementary operations supported by this algorithm follow: `insert`,
    `delete`, `substitute`, and `transpose`.
  * A transposition reorders the characters `ab` as `ba`, erring with a penalty
    of 1 unit instead of 2.
      * The standard algorithm treats transpositions as either a sequence of
        `delete+insert`, `insert+delete`, or `substitute+substitute`, each of
        which errs in a penalty of 2 units.
  * This algorithm is preferred for correcting typographical errors, where the
    majority of misspellings in English are within 2 units of error from the
    intended spelling with many errors being transpositions.
3. `liblevenshtein::Algorithm::MERGE_AND_SPLIT`
  * Standard Levenshtein distance extended with two additional elementary
    operations: `merge` and `split`.
  * The elementary operations supported by this algorithm follow: `insert`,
    `delete`, `substitute`, `merge`, and `split`.
  * This algorithm does not include `transpose` as an elementary operation.
  * A `merge` collapses characters `cl` as a single character `d`.
  * A `split` expands character `d` as two characters `cl`.
  * This algorithm is preferred for correcting OCR (Optical Character
    Recognition) errors, where an OCR model may incorrectly read the sequence of
    characters `cl` as `d` or the character `d` as the sequence `cl`. Of course,
    these operations consider all combinations of characters from your
    dictionary and not just the obvious ones.

### Results

`liblevenshtein` supports returning results in two formats:

1. `std::string`
  * Spelling candidates are returned as strings without including their edit
    distances from the query term.
  * This is likely what you want for production.
2. `liblevenshtein::Candidate`
  * Spelling candidates are returned as instances of `std::pair<std::string,
    std::size_t>`, where each pair includes the spelling candidate and its edit
    distance from the query term.
  * This is likely what you want for development.

### Example

```cmake
# file: CMakeLists.txt

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

find_package(Protobuf REQUIRED)
find_package(liblevenshtein REQUIRED)

add_executable(${PROJECT_NAME}
  "main.cpp")

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    protobuf::libprotobuf
    levenshtein)
```

```cpp
// file: main.cpp

#include <algorithm>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include <google/protobuf/stubs/common.h>

#include <liblevenshtein/collection/dawg.h>
#include <liblevenshtein/collection/sorted_dawg.h>
#include <liblevenshtein/transducer/algorithm.h>
#include <liblevenshtein/transducer/transducer.h>
#include <liblevenshtein/serialization/serializer.h>

namespace ll = liblevenshtein;

int main(int argc, char *argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  // path to file containing serialized dictionary
  std::string serialization_path;

  ll::Dawg *dawg = ll::deserialize_protobuf(serialization_path);

  if (dawg == nullptr) {
    std::vector<std::string> terms; // populate with your spelling candidates
    std::sort(terms.begin(), terms.end()); // must be sorted for now

    // NOTE: If (dawg == nullptr) then the construction of the dictionary
    // failed, probably because terms wasn't sorted lexicographically in
    // ascending order.
    dawg = ll::sorted_dawg(terms.begin(), terms.end());
  }

  /**
   * Template arguments:
   * 1. ll::Algorithm to use for searching (options: STANDARD, TRANSPOSITION, or MERGE_AND_SPLIT)
   * 2. Return type for spelling candidates (options: std::string or ll::Candidate)
   *
   * NOTE: ll::Candidate is an alias for std::pair<std::string, std::size_t>
   */
  ll::Transducer<ll::Algorithm::TRANSPOSITION, ll::Candidate> transduce(dawg->root());

  std::string query_term;    // assign the term whose spelling you wish to correct

  std::size_t max_distance = 2;  // maximum number of operations allowed to transform
                                 // a spelling candidate into query_term (edit distance)

  // NOTE: ll:Candidate is an alias for std::pair<std::string, std::size_t>
  for (const ll::Candidate& candidate : transduce(query_term, max_distance)) {
    const std::string& term = candidate.first;     // spelling candidate for query_term

    const std::size_t& distance = candidate.second;  // minimum number of operations required
                                                     // to transform query_term into term
  }

  /**
   * If you had initialized the transducer as
   * ll::Transducer<ll::Algorithm::TRANSPOSITION, std::string>, you'd iterate
   * over the results as follows:
   * for (const std::string& term : transduce(query_term, max_distance)) {
   *   // do something with term, which is guaranteed to require no more
   *   // than max_distance operations to transform it into the query_term.
   * }
   */

  // save the dictionary for reuse
  ll::serialize_protobuf(dawg, serialization_path);

  delete dawg;

  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
```
