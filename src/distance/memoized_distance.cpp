#include "memoized_distance.h"

using namespace std::literals;


namespace liblevenshtein {

    int MemoizedDistance::get_distance(SymmetricImmutablePair<std::string> &key) {
        std::shared_lock reader(mutex);
        auto iter = memo.find(key);
        if (iter != memo.end()) {
            return iter->second;
        }
        return -1;
    }

    int MemoizedDistance::set_distance(SymmetricImmutablePair<std::string> &key, int distance) {
        std::unique_lock writer(mutex);
        memo[key] = distance;
        return distance;
    }

    std::string MemoizedDistance::f(std::string& u, int const t) const {
        if (t < u.length()) {
            return u.substr(1 + t);
        }
        return "";
    }
}
