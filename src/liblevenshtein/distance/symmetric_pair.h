#ifndef __LIBLEVENSHTEIN__DISTANCE__SYMMETRIC_IMMUTABLE_PAIR_H__
#define __LIBLEVENSHTEIN__DISTANCE__SYMMETRIC_IMMUTABLE_PAIR_H__

#include <iostream>
#include <string>

#include "liblevenshtein/utils/MurmurHash2.h"


namespace liblevenshtein {

    class SymmetricPair {
    public:
        SymmetricPair(const std::string &first, const std::string &second);
        bool operator==(const SymmetricPair &other) const;
        bool operator!=(const SymmetricPair &other) const;

        friend class std::hash<SymmetricPair>;
        friend std::ostream &operator<<(std::ostream &out, const SymmetricPair &pair);

      private:
        std::string first;
        std::string second;
    };
} // namespace liblevenshtein


namespace std {

    template <>
    struct hash<liblevenshtein::SymmetricPair> {
        size_t operator()(const liblevenshtein::SymmetricPair &pair) const;
    };
} // namespace std

#endif // __LIBLEVENSHTEIN__COLLECTION__SYMMETRIC_IMMUTABLE_PAIR_H__
