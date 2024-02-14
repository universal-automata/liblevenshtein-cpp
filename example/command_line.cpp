#include <cstring>
#include <filesystem>
#include <iostream>
#include <sstream>

#include <liblevenshtein/transducer/algorithm.h>

#include "command_line.h"

namespace fs = std::filesystem;

namespace ll = liblevenshtein;

namespace liblevenshtein::demo {

CommandLine::CommandLine(int argc, char **argv) : argc(argc), argv(argv) {}

auto CommandLine::dictionary_path() const -> const fs::path & {
  return _dictionary_path;
}

auto CommandLine::serialization_path() const -> const fs::path & {
  return _serialization_path;
}

auto CommandLine::algorithm() const -> const ll::Algorithm & {
  return _algorithm;
}

auto CommandLine::max_distance() const -> std::size_t {
  return _max_distance;
}

auto CommandLine::next_path(fs::path &path, int &i) -> bool {
  if (i + 1 < argc) {
    path = argv[i + 1];
    ++ i;
    return true;
  }
  std::cerr << "Not enough command-line args!" << std::endl;
  _return_code = ReturnCode::RETURN_END_OF_OPTS;
  return false;
}

auto CommandLine::parse_opts() -> bool {
  for (int i = 1; i < argc; ++i) {
    const char *arg = argv[i];
    if (!strcmp(arg, "-h") || !strcmp(arg, "--help")) {
      _return_code = ReturnCode::RETURN_SUCCESS;
      print_help();
      return false;
    } else if (!strcmp(arg, "--dictionary-path")) {
      if (!next_path(_dictionary_path, i)) {
        return false;
      }
      if (!fs::exists(_dictionary_path)) {
        std::cerr << "--dictionary-path=<PATH> must exist!" << std::endl;
        std::cerr << "--dictionary-path=" << _dictionary_path << std::endl;
        _return_code = ReturnCode::RETURN_FILE_NOT_EXISTS;
        return false;
      }
    } else if (!strcmp(arg, "--serialization-path")) {
      if (!next_path(_serialization_path, i)) {
        return false;
      }
    } else if (!strcmp(arg, "--standard")) {
      _algorithm = ll::Algorithm::STANDARD;
    } else if (!strcmp(arg, "--transposition")) {
      _algorithm = ll::Algorithm::TRANSPOSITION;
    } else if (!strcmp(arg, "--merge-and-split")) {
      _algorithm = ll::Algorithm::MERGE_AND_SPLIT;
    } else if (!strcmp(arg, "--max-distance")) {
      if (i + 1 == argc) {
        std::cerr << "Not enough command-line args!" << std::endl;
        _return_code = ReturnCode::RETURN_END_OF_OPTS;
        return false;
      }
      std::stringstream stream(argv[i + 1]);
      stream >> _max_distance;
      ++i;
    } else {
      std::cerr << "Invalid argument: " << arg << std::endl;
      _return_code = ReturnCode::RETURN_INVALID_ARG;
      print_help();
      return false;
    }
  }

  if (!fs::exists(_dictionary_path) && !fs::exists(_serialization_path)) {
    std::cerr << "Either --dictionary-path=<PATH> or "
                 "--serialization-path=<PATH> must exist"
              << std::endl;
    std::cerr << "--dictionary_path=" << _dictionary_path << std::endl;
    std::cerr << "--serialization_path=" << _serialization_path << std::endl;
    _return_code = ReturnCode::RETURN_FILE_NOT_EXISTS;
    return false;
  }

  print_config();
  return true;
}

auto CommandLine::return_code() const -> ReturnCode {
  return _return_code;
}

void CommandLine::print_help() const {
  std::cerr << "liblevenshtein-demo :: Interactively queries a dictionary using the" << std::endl;
  std::cerr << "configuration specified at the comand-line. Either a valid --dictionary-path or" << std::endl;
  std::cerr << "a --serialization-path must be provided." << std::endl;
  std::cerr << "--------------------------------------------------------------------------------" << std::endl;
  std::cerr << "  -h|--help                    Prints this help text." << std::endl;
  std::cerr << "  --dictionary-path <PATH>     Path to the dictionary text file (one term per" << std::endl;
  std::cerr << "                               line)." << std::endl;
  std::cerr << "  --serialization-path <PATH>  Path to the file containing the serialized" << std::endl;
  std::cerr << "                               dictionary." << std::endl;
  std::cerr << "  --standard                   [Optional] Use the standard Levenshtein distance " << std::endl;
  std::cerr << "                               (substitutions, insertions, and deletions)." << std::endl;
  std::cerr << "  --transposition              [Optional] Use the standard Levenshtein distance" << std::endl;
  std::cerr << "                               extended with transposition." << std::endl;
  std::cerr << "  --merge-and-split            [Optional] Use the standard Levenshtein distance" << std::endl;
  std::cerr << "                               extended with merge and split." << std::endl;
  std::cerr << "  --max-distance <VALUE>       Maximum edit distance from the query term for " << std::endl;
  std::cerr << "                               spelling candidates (default: 2)." << std::endl;
  std::cerr << std::endl;
  std::cerr << "Examples:" << std::endl;
  std::cerr << std::endl;
  std::cerr << "  ./liblevenshtein-demo --dictionary-path ../programming-languages.txt \\" << std::endl;
  std::cerr << "                        --serialization-path programming-languages.pb" << std::endl;
}

void CommandLine::print_config() const {
  std::cout << "Using configuration:" << std::endl;
  std::cout << "  dictionary-path: " << _dictionary_path << std::endl;
  std::cout << "  serialization-path: " << _serialization_path << std::endl;
  std::cout << "  algorithm: ";
  switch (_algorithm) {
  case ll::Algorithm::STANDARD:
    std::cout << "standard";
    break;
  case ll::Algorithm::TRANSPOSITION:
    std::cout << "transposition";
    break;
  case ll::Algorithm::MERGE_AND_SPLIT:
    std::cout << "merge-and-split";
    break;
  }
  std::cout << std::endl;
  std::cout << "  max-distance: " << _max_distance << std::endl;
}

} // namespace liblevenshtein::demo
