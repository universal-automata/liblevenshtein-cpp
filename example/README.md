# liblevenshtein-cpp (demo app)

Demonstrates how to use liblevenshtein-cpp.

## Cloning

First, clone the
[liblevenshtein-cpp](https://github.com/universal-automata/liblevenshtein-cpp)
repository:

```shell
git clone https://github.com/universal-automata/liblevenshtein-cpp.git
cd liblevenshtein-cpp
```

## Initializing, building, and installing liblevenshtein-cpp

Before you may build the demo app, please first build and install
[liblevenshtein-cpp](https://github.com/universal-automata/liblevenshtein-cpp).

```shell
mamba env create --force -f environment.yml
conda activate ll-cpp
mkdir build
pushd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX ..
make install
popd
```

## Initializing, building, and executing liblevenshtein-demo

```shell
cd example
mamba env create --force -f environment.yml
conda activate ll-cpp-demo
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

```
$ ./liblevenshtein-demo
Using configuration:
  dictionary-path: "../programming-languages.txt"
  serialization-path: "programming-languages.pb"
  algorithm: transposition
  max-distance: 2

Enter a query term (or nothing to exit).
query> jvaa
d("jvaa", "Java") = 2
d("jvaa", "Lava") = 2

Enter a query term (or nothing to exit).
query>

Exiting ...
```

### Other configuration options:

```
$ ./liblevenshtein-demo --help
liblevenshtein-demo :: Interactively queries a dictionary using the
configuration specified at the comand-line. Either a valid --dictionary-path or
a --serialization-path must be provided.
--------------------------------------------------------------------------------
  -h|--help                    Prints this help text.
  --dictionary-path <PATH>     Path to the dictionary text file (one term per
                               line).
  --serialization-path <PATH>  Path to the file containing the serialized
                               dictionary.
  --standard                   [Optional] Use the standard Levenshtein distance
                               (substitutions, insertions, and deletions).
  --transposition              [Optional] Use the standard Levenshtein distance
                               extended with transposition.
  --merge-and-split            [Optional] Use the standard Levenshtein distance
                               extended with merge and split.
  --max-distance <VALUE>       Maximum edit distance from the query term for
                               spelling candidates (default: 2).

Examples:

  ./liblevenshtein-demo --dictionary-path ../programming-languages.txt \
                        --serialization-path programming-languages.pb
```
