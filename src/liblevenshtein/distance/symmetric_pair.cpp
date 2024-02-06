#include <cstdint>

#include "liblevenshtein/distance/symmetric_pair.h"
#include "liblevenshtein/utils/MurmurHash2.h"

namespace liblevenshtein {

    SymmetricPair::SymmetricPair(const std::string &first, const std::string &second) {
        if (first.compare(second) < 0) {
            this->first = first;
            this->second = second;
        } else {
            this->first = second;
            this->second = first;
        }
    }

    bool SymmetricPair::operator==(const SymmetricPair &other) const {
        int const comparison = first.compare(other.first);
        if (comparison != 0) {
            return false;
        }
        return 0 == second.compare(other.second);
    }

    bool SymmetricPair::operator!=(const SymmetricPair &other) const {
        return !(*this == other);
    }

    std::ostream& operator<<(std::ostream &out, const SymmetricPair &pair) {
        out << "SymmetricPair{first=\"" << pair.first << "\", second=\"" << pair.second << "\"}";
        return out;
    }

} // namespace liblevenshtein

std::size_t std::hash<liblevenshtein::SymmetricPair>::operator()(const liblevenshtein::SymmetricPair &pair) const {
    std::uint64_t hash_code = 0xDEADBEEF;
    hash_code = MurmurHash64A(pair.first.c_str(), pair.first.length(), hash_code);
    return MurmurHash64A(pair.second.c_str(), pair.second.length(), hash_code);
}
