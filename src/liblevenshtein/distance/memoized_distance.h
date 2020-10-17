#ifndef __LIBLEVENSHTEIN__DISTANCE__MEMOIZED_DISTANCE_H__
#define __LIBLEVENSHTEIN__DISTANCE__MEMOIZED_DISTANCE_H__

#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>

#include "liblevenshtein/collection/symmetric_pair.h"
#include "liblevenshtein/distance/distance.h"

namespace liblevenshtein {

    class MemoizedDistance : public Distance {
    public:
        int operator()(std::string v, std::string w);

    protected:
        int get_distance(const SymmetricPair &key);
        int set_distance(const SymmetricPair &key, int const distance);
        std::string f(std::string& u, int t) const;

    private:
        std::unordered_map<SymmetricPair, int> memo;
        mutable std::shared_mutex mutex;
    };
} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__DISTANCE__MEMOIZED_DISTANCE_H__
