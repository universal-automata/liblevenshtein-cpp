#include <cstdio>
#include <stdlib.h>
#include <sstream>

#include <stdexcept>
#include <yaml-cpp/yaml.h>

#include "rapidcheck_parser.h"


namespace liblevenshtein {

    RapidCheckParser::RapidCheckParser(const std::filesystem::path& config_path)
        : config_path(config_path)
    {}

    std::string RapidCheckParser::parse() {
        std::stringstream ss;

        YAML::Node config = YAML::LoadFile(config_path.c_str());

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
            ss << "max_discard_ratio=" << config["max_discard_ratio"].as<std::string>() << " ";
        }

        if (config["noshrink"]) {
            ss << "noshrink=" << config["noshrink"].as<std::string>() << " ";
        }

        if (config["verbose_progress"]) {
            ss << "verbose_progress=" << config["verbose_progress"].as<std::string>() << " ";
        }

        if (config["verbose_shrinking"]) {
            ss << "verbose_shrinking=" << config["verbose_shrinking"].as<std::string>() << " ";
        }

        if (config["reproduce"]) {
            ss << "reproduce=" << config["reproduce"].as<std::string>() << " ";
        }

        return ss.str();
    }

    void init_rapidcheck(char* executable) {
        fs::path config_path = fs::canonical(executable).parent_path() / "rapidcheck.yaml";
        RapidCheckParser config_parser(config_path);
        setenv("RC_PARAMS", config_parser.parse().c_str(), 1);
    }
} // namespace liblevenshtein
