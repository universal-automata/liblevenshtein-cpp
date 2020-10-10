#ifndef __LIBLEVENSHTEIN__COLLECTION__SYMMETRIC_IMMUTABLE_PAIR_H__
#define __LIBLEVENSHTEIN__COLLECTION__SYMMETRIC_IMMUTABLE_PAIR_H__

#include <string>

#include "../utils/MurmurHash2.h"


namespace liblevenshtein {

    class SymmetricImmutablePair {
    public:
        SymmetricImmutablePair(std::string &first, std::string &second);
        bool operator==(const SymmetricImmutablePair &other) const;
    private:
        std::string first;
        std::string second;

        // for hash code
        friend class std::hash<liblevenshtein::SymmetricImmutablePair>;
    };
} // namespace liblevenshtein


namespace std {

    template <>
    struct hash<liblevenshtein::SymmetricImmutablePair> : unary_function<liblevenshtein::SymmetricImmutablePair, size_t> {
        size_t operator()(const liblevenshtein::SymmetricImmutablePair &pair) const;
    };
} // namespace std

#endif // __LIBLEVENSHTEIN__COLLECTION__SYMMETRIC_IMMUTABLE_PAIR_H__
