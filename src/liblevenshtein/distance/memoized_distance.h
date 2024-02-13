#ifndef LIBLEVENSHTEIN_DISTANCE_MEMOIZED_DISTANCE_H
#define LIBLEVENSHTEIN_DISTANCE_MEMOIZED_DISTANCE_H

#include <shared_mutex>
#include <string>
#include <unordered_map>

#include "liblevenshtein/distance/distance.h"
#include "liblevenshtein/distance/symmetric_pair.h"

namespace liblevenshtein {

  class MemoizedDistance : public Distance {
  public:
    auto operator()(const std::string &v, const std::string &w) -> std::size_t override;

  protected:
    auto get(const SymmetricPair &key, std::size_t &distance) -> bool;
    auto set(const SymmetricPair &key, const std::size_t &distance)
        -> std::size_t;
    static auto f(const std::string &u, std::size_t t) -> std::string;

  private:
    std::unordered_map<SymmetricPair, std::size_t> memo;
    mutable std::shared_mutex mutex;
  };

} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_DISTANCE_MEMOIZED_DISTANCE_H
