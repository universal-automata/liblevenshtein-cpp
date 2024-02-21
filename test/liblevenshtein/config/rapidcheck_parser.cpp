#include <sstream>

#include <yaml-cpp/yaml.h>

#include "liblevenshtein/config/rapidcheck_parser.h"

namespace liblevenshtein {

// NOLINTNEXTLINE(modernize-pass-by-value)
RapidCheckParser::RapidCheckParser(const std::filesystem::path &config_path)
    : config_path(config_path) {}

auto RapidCheckParser::parse() -> std::string {
  std::stringstream ss;

  YAML::Node config = YAML::LoadFile(config_path.generic_string());

  if (config["seed"]) {
    ss << "seed=" << config["seed"].as<std::string>() << " ";
  }

  if (config["max_success"]) {
    ss << "max_success=" << config["max_success"].as<std::string>() << " ";
  }

  if (config["max_size"]) {
    ss << "max_size=" << config["max_size"].as<std::string>() << " ";
  }

  if (config["max_discard_ratio"]) {
    ss << "max_discard_ratio=" << config["max_discard_ratio"].as<std::string>()
       << " ";
  }

  if (config["noshrink"]) {
    ss << "noshrink=" << config["noshrink"].as<std::string>() << " ";
  }

  if (config["verbose_progress"]) {
    ss << "verbose_progress=" << config["verbose_progress"].as<std::string>()
       << " ";
  }

  if (config["verbose_shrinking"]) {
    ss << "verbose_shrinking=" << config["verbose_shrinking"].as<std::string>()
       << " ";
  }

  if (config["reproduce"]) {
    ss << "reproduce=" << config["reproduce"].as<std::string>() << " ";
  }

  return ss.str();
}

void init_rapidcheck(const char* executable) {
  fs::path config_path =
      fs::canonical(executable).parent_path() / "rapidcheck.yaml";
  RapidCheckParser config_parser(config_path);
#if _MSC_VER && !__INTEL_COMPILER
  SetEnvironmentVariable("RC_PARAMS", config_parser.parse().c_str());
#else
  // NOLINTNEXTLINE(concurrency-mt-unsafe)
  setenv("RC_PARAMS", config_parser.parse().c_str(), 1);
#endif
}

} // namespace liblevenshtein
