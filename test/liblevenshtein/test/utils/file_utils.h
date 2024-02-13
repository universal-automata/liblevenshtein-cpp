#ifndef __LIBLEVENSHTEIN__TEST__UTILS__FILE_UTILS_H__
#define __LIBLEVENSHTEIN__TEST__UTILS__FILE_UTILS_H__

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

namespace liblevenshtein::test {

auto gen_rand_str(const size_t &length) -> std::string;

auto gen_temp_path(const std::string &prefix, const std::string &ext)
    -> fs::path;

} // namespace liblevenshtein::test

#endif // __LIBLEVENSHTEIN__TEST__UTILS__FILE_UTILS_H__
