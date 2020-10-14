# liblevenshtein

## C++

### A library for generating Finite State Transducers based on Levenshtein Automata.

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

#### Testing

#### Dependencies
1. [Google Test](https://github.com/google/googletest)
2. [RapidCheck](https://github.com/emil-e/rapidcheck)
3. [yaml-cpp](https://github.com/jbeder/yaml-cpp)
