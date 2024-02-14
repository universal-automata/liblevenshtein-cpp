# liblevenshtein-cpp

| Action Type | Build Status |||
|        ---: |    :---:     | :---: | :---: |
| **Operating System** | [![Test Ubuntu](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/test-ubuntu.yml/badge.svg)](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/test-ubuntu.yml) | [![Test MacOS](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/test-macos.yml/badge.svg)](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/test-macos.yml) | [![Test Windows](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/test-windows.yml/badge.svg)](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/test-windows.yml) |
| **Engineering Excellence** | [![Coverage Status](https://coveralls.io/repos/github/universal-automata/liblevenshtein-cpp/badge.svg?branch=master)](https://coveralls.io/github/universal-automata/liblevenshtein-cpp?branch=master) | [![Linter](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/linter.yml/badge.svg)](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/linter.yml) | [![CodeQL](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/codeql.yml/badge.svg)](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/codeql.yml) |
| **Demo App** | [![Run Demo](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/run-demo.yml/badge.svg)](https://github.com/universal-automata/liblevenshtein-cpp/actions/workflows/run-demo.yml) |||

A library for generating Finite State Transducers based on Levenshtein Automata.

NOTE: This library is currently in rc phase. I'll have it production ready as
soon as possible. Currently, there is >90% test coverage over the sources and
the library is usable as described below.

Due to limited resources on my part, this library requires C++20 features (or
whichever is the latest standard). If you need compatibility with an older
standard, please either submit a pull request (preferably) or create an issue
stating the standard you need compatibility with and I will comply if I can.

For a demonstration, please reference the [example app](example/).

## Initialization

To ease dependency management during development,
[Anaconda](https://www.anaconda.com/) is used but should not be required if you
have the necessary libraries installed. If you do not have a working
[Anaconda](https://www.anaconda.com/) installation, I recommend the
[Mamba](https://mamba.readthedocs.io/en/latest/installation/mamba-installation.html)
variant:

```shell
# For Linux (x86_64)
wget https://github.com/conda-forge/miniforge/releases/latest/download/Miniforge3-Linux-x86_64.sh
bash Miniforge3-Linux-x86_64.sh -b
```

```shell
# For OS X (arm64)
wget https://github.com/conda-forge/miniforge/releases/latest/download/Miniforge3-MacOSX-arm64.sh
bash Miniforge3-MacOSX-arm64.sh -b
```

TODO: Add instructions for Windows.

Initialize the `base` environment:

```bash
__conda_setup="$("$HOME/miniforge3/bin/conda" 'shell.bash' 'hook' 2> /dev/null)"
if [ $? -eq 0  ]; then
    eval "$__conda_setup"
else
    if [ -f "$HOME/miniforge3/etc/profile.d/conda.sh"  ]; then
        source "$HOME/miniforge3/etc/profile.d/conda.sh"
    else
        export PATH="$HOME/miniforge3/bin:$PATH"
    fi
fi
```

Clone [liblevenshtein-cpp](https://github.com/universal-automata/liblevenshtein-cpp):

```shell
git clone https://github.com/universal-automata/liblevenshtein-cpp.git
cd liblevenshtein-cpp
```

Initialize the conda environment:

```shell
mamba env create --force -f environment.yml
conda activate ll-cpp
```

## Building and Installation

```shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX ..
make
make install
```

The files will be installed to the following locations:

```
$ tree "${CMAKE_INSTALL_PREFIX}"
${CMAKE_INSTALL_PREFIX}
├── include
│   ├── MurmurHash2.h
│   ├── MurmurHash3.h
│   └── liblevenshtein
│       ├── collection
│       │   ├── dawg.h
│       │   ├── dawg_iterator.h
│       │   ├── dawg_node.h
│       │   ├── prefix.h
│       │   ├── sorted_dawg.h
│       │   └── transition.h
│       ├── distance
│       │   ├── distance.h
│       │   ├── memoized_distance.h
│       │   ├── merge_and_split_distance.h
│       │   ├── standard_distance.h
│       │   ├── symmetric_pair.h
│       │   └── transposition_distance.h
│       ├── proto
│       │   └── liblevenshtein.pb.h
│       ├── serialization
│       │   └── serializer.h
│       └── transducer
│           ├── algorithm.h
│           ├── comparator.h
│           ├── distance.h
│           ├── intersection.h
│           ├── lazy_query.h
│           ├── merge.h
│           ├── position.h
│           ├── position_transition.h
│           ├── state.h
│           ├── state_iterator.h
│           ├── state_transition.h
│           ├── subsumes.h
│           ├── transducer.h
│           └── unsubsume.h
└── lib
    ├── cmake
    │   └── liblevenshtein
    │       ├── liblevenshtein-config-version.cmake
    │       ├── liblevenshtein-config.cmake
    │       ├── liblevenshtein-targets-release.cmake
    │       └── liblevenshtein-targets.cmake
    ├── liblevenshtein.so -> liblevenshtein.so.4.0
    ├── liblevenshtein.so.4.0 -> liblevenshtein.so.4.0.0
    └── liblevenshtein.so.4.0.0

11 directories, 37 files
```

### Enabling tests

If you want to build the library with tests, use the same instructions but
add the CMake option `BUILD_TESTS=ON`, as described below:

```shell
cmake -DCMAKE_BUILD_TYPE=Debug \
      -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX \
      -DBUILD_TESTS=ON \
      ..
```

### Enabling baseline metrics

If you want to enable the baseline metrics for validation, you must pass
`-DBUILD_BASELINE_METRICS=ON` to CMake:

```shell
cmake -DCMAKE_BUILD_TYPE=Debug \
      -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX \
      -DBUILD_BASELINE_METRICS=ON \
      ..
```

The baseline metrics are intended for validation of the search results but might
be useful if you need to compute edit distances among individual pairs of terms.

NOTE: The baseline metrics are required for the tests and will be implicitly
enabled for them if the baseline metrics are not explicitly enabled.

## Usage

### Algorithms

`liblevenshtein` supports three variations of Levenshtein distance, where each
variation is defined by the elementary operations it supports. An elementary
operation is an edit operation that errs in a penalty of 1 unit.

1. `liblevenshtein::STANDARD`
  * Standard Levenshtein distance including the traditional elementary
    operations of `insert`, `delete`, and `substitute`.
2. `liblevenshtein::TRANSPOSITION`
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
3. `liblevenshtein::MERGE_AND_SPLIT`
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
  "command_line.cpp"
  "main.cpp")

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    protobuf::libprotobuf
    levenshtein)

```

```c++
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

    std::string query_term;        // assign the term whose spelling you wish to correct

    std::size_t max_distance = 2;  // maximum number of operations allowed to transform
                                   // a spelling candidate into query_term (edit distance)

    // NOTE: ll:Candidate is an alias for std::pair<std::string, std::size_t>
    for (const ll::Candidate& candidate : transduce(query_term, max_distance)) {
        const std::string& term = candidate.first;       // spelling candidate for query_term

        const std::size_t& distance = candidate.second;  // minimum number of operations required
                                                         // to transform query_term into term
    }

    /**
     * If you had initialized the transducer as
     * ll::Transducer<ll::Algorithm::TRANSPOSITION, std::string>, you'd iterate
     * over the results as follows:
     * for (const std::string& term : transduce(query_term, max_distance)) {
     *     // do something with term, which is guaranteed to require no more
     *     // than max_distance operations to transform it into the query_term.
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

## Testing

```shell
# Within the build directory
./test/test-liblevenshtein
```

### Dependencies

For the most up-to-date list of dependencies, please reference
[environment.yml](environment.yml).

1. [CMake](https://cmake.org/)
2. [Make](https://www.gnu.org/software/make/)
3. C++ Compiler:
    - Linux:
        - [g++](https://gcc.gnu.org/)
        - [clang++](https://clang.llvm.org/)
    - MacOS:
        - [clang++](https://clang.llvm.org/)
    - Windows:
        - [vc++](https://visualstudio.microsoft.com/)
4. [Protocol Buffers](https://protobuf.dev/)
5. [Google Test](https://github.com/google/googletest)
6. [RapidCheck](https://github.com/emil-e/rapidcheck)
7. [yaml-cpp](https://github.com/jbeder/yaml-cpp)
