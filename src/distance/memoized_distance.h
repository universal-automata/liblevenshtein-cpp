#ifndef __LIBLEVENSHTEIN__DISTANCE__MEMOIZED_DISTANCE_H__
#define __LIBLEVENSHTEIN__DISTANCE__MEMOIZED_DISTANCE_H__

#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>

#include "../collection/symmetric_immutable_pair.hpp"
#include "distance.h"

namespace liblevenshtein {

    class MemoizedDistance : public Distance<std::string> {
    protected:
        int get_distance(SymmetricImmutablePair<std::string> &key);
        int set_distance(SymmetricImmutablePair<std::string> &key, int distance);
        std::string f(std::string& u, int t) const;
    private:
        std::unordered_map<SymmetricImmutablePair<std::string>, int> memo;
        mutable std::shared_mutex mutex;
    };
}


#endif // __LIBLEVENSHTEIN__DISTANCE__MEMOIZED_DISTANCE_H__
