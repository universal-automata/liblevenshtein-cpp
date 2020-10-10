#ifndef __LIBLEVENSHTEIN__COLLECTION__SYMMETRIC_IMMUTABLE_PAIR_H__
#define __LIBLEVENSHTEIN__COLLECTION__SYMMETRIC_IMMUTABLE_PAIR_H__

#include <string>

#include "../utils/MurmurHash2.h"


namespace liblevenshtein {

    template <class Type>
    class SymmetricImmutablePair {
    public:
        SymmetricImmutablePair(Type first, Type second);
    private:
        Type first;
        Type second;
    };

    template <>
    class SymmetricImmutablePair<std::string> {
    public:

        SymmetricImmutablePair(std::string first, std::string second) {
            if (first.compare(second) < 0) {
                this->first = first;
                this->second = second;
            } else {
                this->first = second;
                this->second = first;
            }
        }

        bool operator==(const SymmetricImmutablePair<std::string> &other) const {
            int const comparison = first.compare(other.first);
            if (comparison == 0) {
                return 0 == second.compare(other.second);
            }
            return comparison;
        }

    private:
        std::string first;
        std::string second;

        // for hash code
        friend class std::hash<liblevenshtein::SymmetricImmutablePair<std::string>>;
    };
}

template <>
struct std::hash<liblevenshtein::SymmetricImmutablePair<std::string>> {
    std::size_t operator()(const liblevenshtein::SymmetricImmutablePair<std::string> &pair) const {
        std::uint64_t hash_code = 0xDEADBEEF;
        hash_code = MurmurHash64A(pair.first.c_str(), pair.first.length(), hash_code);
        return MurmurHash64A(pair.second.c_str(), pair.second.length(), hash_code);
    }
};


#endif // __LIBLEVENSHTEIN__COLLECTION__SYMMETRIC_IMMUTABLE_PAIR_H__
