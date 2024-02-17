#ifndef LIBLEVENSHTEIN_DISTANCE_DISTANCE_H
#define LIBLEVENSHTEIN_DISTANCE_DISTANCE_H

#include <string>

namespace liblevenshtein::distance {

/**
 * Metric that measures the edit distance between two terms, denoted `d(v,w)`.
 * The edit distance is the minimum number of elementary operations required to
 * transform one term into the other, but it does not describe a unique
 * combination of transformations. Elementary operations consist of insertion,
 * deletion, and substitution, and any others specific to each implementation.
 *
 * A distance metric satisfies the following axioms:
 *   1. `d(x, y) = 0, if x = y`
 *   2. `d(x, y) > 0, if x != y`
 *   3. `d(x, y) = d(y, x)`
 *   4. `d(x, z) <= d(x, y) + d(y, z)`
 */
class Distance {
public:

  /**
   * Measures the edit distance between two terms.
   *
   * @param v First term to compare.
   * @param w Second term to compare.
   * @return Edit distance between v and w.
   */
  virtual auto between(std::string v, std::string w) -> std::size_t = 0;

  /**
   * Measures the edit distance between two terms. This is equivalent to calling
   * `between(v, w)`.
   *
   * @param v First term to compare.
   * @param w Second term to compare.
   * @return Edit distance between v and w.
   */
  auto operator()(const std::string &v, const std::string &w) -> std::size_t;
};

} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_DISTANCE_DISTANCE_H
