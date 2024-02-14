#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include <cstdint>
#include <filesystem>

#include <liblevenshtein/transducer/algorithm.h>

namespace fs = std::filesystem;

namespace ll = liblevenshtein;

namespace liblevenshtein::demo {

enum class ReturnCode {
  RETURN_SUCCESS = 0,
  RETURN_FAILURE = 1,
  RETURN_END_OF_OPTS = 2,
  RETURN_FILE_NOT_EXISTS = 3,
  RETURN_INVALID_ARG = 4,
  RETURN_DEFAULT = RETURN_SUCCESS
};

class CommandLine {
public:
  CommandLine(int argc, char **argv);
  ~CommandLine() = default;

  auto dictionary_path() const -> const fs::path &;
  auto serialization_path() const -> const fs::path &;
  auto algorithm() const -> const ll::Algorithm &;
  auto max_distance() const -> std::size_t;

  auto parse_opts() -> bool;

  auto return_code() const -> ReturnCode;

  void print_help() const;
  void print_config() const;

private:
  auto next_path(fs::path &path, int &i) -> bool;

  ReturnCode _return_code = ReturnCode::RETURN_DEFAULT;
  fs::path _dictionary_path = "../resources/programming-languages.txt";
  fs::path _serialization_path = "programming-languages.pb";
  ll::Algorithm _algorithm = ll::Algorithm::TRANSPOSITION;
  std::size_t _max_distance = 2;

  int argc;
  char **argv;
};

} // namespace liblevenshtein::demo

#endif // COMMAND_LINE_H
