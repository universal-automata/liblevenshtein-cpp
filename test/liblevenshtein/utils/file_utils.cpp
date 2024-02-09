#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <vector>

#include "liblevenshtein/utils/file_utils.h"

namespace fs = std::filesystem;

namespace liblevenshtein::test {

// see: https://stackoverflow.com/a/12468109
std::string gen_rand_str(const size_t &length) {
    auto randchar = []() -> char {
        const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[rand() % max_index];
    };
    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);
    return str;
}

fs::path gen_temp_path(const std::string &prefix, const std::string &ext) {
    static std::vector<fs::path> gend_paths;

    fs::path temp_dir = fs::temp_directory_path();
    fs::path temp_nym;

    do {
        std::string rand_str = gen_rand_str(10);
        std::string file_nym;
        if (ext.length() > 0 && ext.find_first_of('.') != 0) {
            file_nym = prefix + rand_str + "." + ext;
        } else {
            file_nym = prefix + rand_str + ext;
        }
        temp_nym = temp_dir / file_nym;
    } while (fs::exists(temp_nym));

    gend_paths.push_back(temp_nym);
    if (gend_paths.size() == 1) {
        std::atexit([]() {
            for (const fs::path &gend_path : gend_paths) {
                if (fs::exists(gend_path)) {
                    fs::remove(gend_path);
                }
            }
        });
    }

    return temp_nym;
}

} // namespace liblevenshtein::test
