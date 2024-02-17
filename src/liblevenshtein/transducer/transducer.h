#ifndef LIBLEVENSHTEIN_TRANSDUCER_TRANSDUCER_H
#define LIBLEVENSHTEIN_TRANSDUCER_TRANSDUCER_H

#include <cstddef>
#include <string>
#include <utility>

#include "liblevenshtein/collection/dawg_node.h"
#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/intersection.h"
#include "liblevenshtein/transducer/lazy_query.h"

namespace liblevenshtein {

/** Spelling candidate that includes both the dictionary term and its edit
distance from the query term. */
using Candidate = std::pair<std::string, std::size_t>;

/**
 * Constructs a Levenshtein Transducer that, when given a dictionary automaton,
 * query term, and maximum edit distance, `n`, is able to match all spelling
 * candidates in the dictionary automaton for the query term whose edit
 * distances are no larger than `n`.
 */
template <Algorithm Type, class Result>
class Transducer {
public:

  /**
   * Constructs a Levenshtein Transducer around the root DawgNode of a Dawg
   * dictionary.
   *
   * @param root Root DawgNode for some Dawg dictionary.
   */
  Transducer(DawgNode *root);

  /**
   * Frees any owned allocations.
   */
  ~Transducer();

  /**
   * Transduces the query `term` and `max_distance` into the set of all spelling
   * candidates from the dictionary automaton whose edit distances from `term`
   * are no greater than `max_distance`.
   *
   * @param term Query term for spelling correction.
   * @param max_distance Maximum edit distance to consider when matching
   * spelling candidates.
   * @return An iterator over the spelling candidates from the dictionary
   * automaton whose edit distances from `term` are no greater than
   * `max_distance`.
   */
  auto operator()(const std::string &term, std::size_t max_distance = 2)
    -> LazyIterator<Result>;

private:

  /** Initial intersection between the Levenshtein automaton and dictionary
  automaton. */
  Intersection *_intersection;
};

} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_TRANSDUCER_TRANSDUCER_H
