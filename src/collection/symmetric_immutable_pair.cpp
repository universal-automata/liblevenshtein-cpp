#include "symmetric_immutable_pair.h"
#include "../utils/MurmurHash2.h"


namespace liblevenshtein {

    SymmetricImmutablePair::SymmetricImmutablePair(std::string &first, std::string &second) {
        if (first.compare(second) < 0) {
            this->first = first;
            this->second = second;
        } else {
            this->first = second;
            this->second = first;
        }
    }

    bool SymmetricImmutablePair::operator==(const SymmetricImmutablePair &other) const {
        int const comparison = first.compare(other.first);
        if (comparison == 0) {
            return 0 == second.compare(other.second);
        }
        return comparison;
    }
} // namespace liblevenshtein


std::size_t std::hash<liblevenshtein::SymmetricImmutablePair>::operator()(const liblevenshtein::SymmetricImmutablePair &pair) const {
    std::uint64_t hash_code = 0xDEADBEEF;
    hash_code = MurmurHash64A(pair.first.c_str(), pair.first.length(), hash_code);
    return MurmurHash64A(pair.second.c_str(), pair.second.length(), hash_code);
}
