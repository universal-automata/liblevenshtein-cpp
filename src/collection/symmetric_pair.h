#ifndef __LIBLEVENSHTEIN__COLLECTION__SYMMETRIC_IMMUTABLE_PAIR_H__
#define __LIBLEVENSHTEIN__COLLECTION__SYMMETRIC_IMMUTABLE_PAIR_H__

#include <string>

#include "../utils/MurmurHash2.h"


namespace liblevenshtein {

    class SymmetricPair {
    public:
        SymmetricPair(std::string &first, std::string &second);
        bool operator==(const SymmetricPair &other) const;
        bool operator!=(const SymmetricPair &other) const;

      private:
        std::string first;
        std::string second;

        // for hash code
        friend class std::hash<liblevenshtein::SymmetricPair>;
    };
} // namespace liblevenshtein


namespace std {

    template <>
    struct hash<liblevenshtein::SymmetricPair> : unary_function<liblevenshtein::SymmetricPair, size_t> {
        size_t operator()(const liblevenshtein::SymmetricPair &pair) const;
    };
} // namespace std

#endif // __LIBLEVENSHTEIN__COLLECTION__SYMMETRIC_IMMUTABLE_PAIR_H__
