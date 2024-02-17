#ifndef LIBLEVENSHTEIN_DISTANCE_MEMOIZED_DISTANCE_H
#define LIBLEVENSHTEIN_DISTANCE_MEMOIZED_DISTANCE_H

#include <shared_mutex>
#include <string>
#include <unordered_map>

#include "liblevenshtein/distance/distance.h"
#include "liblevenshtein/distance/symmetric_pair.h"

namespace liblevenshtein::distance {

/**
 * Memoizes the distance between pairs of terms.
 */
class MemoizedDistance : public Distance {
protected:

  /**
   * Collects the memoized distance between the pair of terms represented by the
   * SymmetricPair if the distance has been previously determined. Otherwise,
   * the distance is not collected and false is returned.
   *
   * @param key SymmetricPair of terms whose distance may have been memoized.
   * @param distance Outgoing reference containing the memoized distance between
   * the pair of terms, if the distance has been previously determined.
   * @return Whether the distance between the pair of terms has been previously
   * determined.
   */
  auto get(const SymmetricPair &key, std::size_t &distance) -> bool;

  /**
   * Memoizes the distance between the SymmetricPair of terms for future
   * reference.
   *
   * @param key SymmetricPair of terms whose distance is to be memoized.
   * @param distance Distance between the SymmetricPair of terms to memoize.
   * @return The distance once it has been memoized.
   */
  auto set(const SymmetricPair &key, const std::size_t &distance)
      -> std::size_t;

  /**
   * Returns the suffix of \f$u\f$ from position \f$t\f$. If \f$t \ge
   * \left|u\right|\f$, then the empty string is returned.
   *
   * @param u Term whose suffix is to be returned.
   * @param t Beginning position in `u` for the substring.
   * @return The substring of `u` beginning at position `t` if \f$t <
   * \left|u\right|\f$, or the empty string otherwise.
   */
  static auto f(const std::string &u, std::size_t t) -> std::string;

private:

  /** Memoized distances between pairs of terms. */
  std::unordered_map<SymmetricPair, std::size_t> memo;

  /** Coordinates memoization among threads. */
  mutable std::shared_mutex mutex;
};

} // namespace liblevenshtein::distance

#endif // LIBLEVENSHTEIN_DISTANCE_MEMOIZED_DISTANCE_H
