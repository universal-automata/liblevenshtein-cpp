# liblevenshtein

## C++

### A library for generating Finite State Transducers based on Levenshtein Automata.

NOTE: This library is currently in beta phase. I'll have it production ready as
soon as possible. Currently, the top-level components have decent test coverage
and the library is usable as described below.

To make my life easier, this library takes advantage of C++17 features. If you
need compatibility with an older standard, please either submit a pull request
or create an issue stating the standard you need compatibility with and I'll get
around to adding its support when I get time.

#### Building and Installation

```shell
git clone https://github.com/universal-automata/liblevenshtein-cpp.git
cd liblevenshtein-cpp
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Debug -D CMAKE_INSTALL_PREFIX=/usr/local ..
make
make install
```

##### Disabling tests

If you want to build the library without tests, use the same instructions but
add the CMake option `BUILD_TESTS=OFF`, as described below:

```shell
# ...
cmake -D CMAKE_BUILD_TYPE=Debug \
      -D CMAKE_INSTALL_PREFIX=/usr/local \
      -D BUILD_TESTS=OFF \
      ..
# ...
```

##### Disabling baseline metrics

If you want to disable the baseline metrics used for validation, you need to
disable both tests and the metrics. If you disable the metrics but enable tests
then they will be built anyway because they are required for the tests.

```shell
# ...
cmake -D CMAKE_BUILD_TYPE=Debug \
      -D CMAKE_INSTALL_PREFIX=/usr/local \
      -D BUILD_BASELINE_METRICS=OFF \
      -D BUILD_TESTS=OFF \
      ..
# ...
```

#### Usage

```c++
#include <algorithm>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include <liblevenshtein/collection/dawg.h>
#include <liblevenshtein/collection/sorted_dawg.h>
#include <liblevenshtein/transducer/algorithm.h>
#include <liblevenshtein/transducer/transducer.h>

namespace ll = liblevenshtein;

int main(int argc, char *argv[]) {
    std::vector<std::string> terms; // populate with your spelling candidates
    std::sort(terms.begin(), terms.end()); // must be sorted for the current algorithm

    // NOTE: If (dawg == nullptr) then the construction of the dictionary failed,
    // probably because terms wasn't sorted lexicographically in ascending order.
    ll::Dawg *dawg = ll::sorted_dawg(terms.begin(), terms.end());

    /**
     * Template arguments:
     * 1. ll::Algorithm to use for searching (options: STANDARD, TRANSPOSITION, or MERGE_AND_SPLIT)
     * 2. Return type for spelling candidates (options: std::string or ll::Candidate)
     *
     * NOTE: ll::Candidate is an alias for std::pair<std::string, std::size_t>
     */
    ll::Transducer<ll::Algorithm::TRANSPOSITION, ll::Candidate> transduce(dawg->root());

    std::string query_term;        // assign the term whose spelling you wish to correct
    std::size_t max_distance = 2;  // maximum edit distance from query_term

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

     delete dawg;
}
```

#### Testing

```shell
# Within the build directory
for MODULE in collection distance transducer; do
  ./test/liblevenshtein/${MODULE}/test-${MODULE}
done
```

##### Dependencies
1. [Google Test](https://github.com/google/googletest)
2. [RapidCheck](https://github.com/emil-e/rapidcheck)
3. [yaml-cpp](https://github.com/jbeder/yaml-cpp)
