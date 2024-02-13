#ifndef __LIBLEVENSHTEIN__TEST__RAPIDCHECK_PARSER_H__
#define __LIBLEVENSHTEIN__TEST__RAPIDCHECK_PARSER_H__

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

namespace liblevenshtein {

class RapidCheckParser {
public:
  RapidCheckParser(const fs::path &config_path);
  auto parse() -> std::string;

private:
  const fs::path config_path;
};

void init_rapidcheck(const char* executable);

} // namespace liblevenshtein

#endif // __LIBLEVENSHTEIN__TEST__RAPIDCHECK_PARSER_H__
