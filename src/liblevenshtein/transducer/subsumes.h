#ifndef LIBLEVENSHTEIN_TRANSDUCER_SUBSUMES_H
#define LIBLEVENSHTEIN_TRANSDUCER_SUBSUMES_H

#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/position.h"

namespace liblevenshtein {

/**
 * Returns whether Position `lhs` subsumes Position `rhs`, given the maximum
 * edit distance `n`. We say that `lhs` subsumes `rhs` if the set of spelling
 * candidates reachable from `rhs` is a subset of the spelling candidates
 * reachable from `lhs`. As such, if `lhs` subsumes `rhs`, then `rhs` is
 * redundant and may be removed from the set of candidate Positions. In fact, it
 * must be removed for the current set of algorithms to perform correctly.
 *
 * @param lhs Position to compare against `rhs`.
 * @param rhs Position to compare against `lhs`.
 * @param n Maximum edit distance to consider when matching spelling candidates.
 * @return Whether `lhs` subsumes `rhs`, given the maximum edit distance `n`.
 */
template <Algorithm Type>
auto subsumes(Position *lhs, Position *rhs, std::size_t n) -> bool;

/**
 * Returns whether `lhs` subsumes `rhs` according to the subsumption rules of
 * standard Levenshtein distance, which consists of the elementary operations of
 * insertion, deletion, and substitution.
 *
 * @param lhs Position to compare against `rhs`.
 * @param rhs Position to compare against `lhs`.
 * @param n Maximum edit distance to consider when matching spelling candidates.
 * @return Whether `lhs` subsumes `rhs`, given the maximum edit distance `n`.
 */
template <>
auto subsumes<Algorithm::STANDARD>(Position *lhs, Position *rhs, std::size_t n)
    -> bool;

/**
 * Returns whether `lhs` subsumes `rhs` according to the subsumption rules of
 * standard Levenshtein distance extended with the elementary operation of
 * transposition.
 *
 * @param lhs Position to compare against `rhs`.
 * @param rhs Position to compare against `lhs`.
 * @param n Maximum edit distance to consider when matching spelling candidates.
 * @return Whether `lhs` subsumes `rhs`, given the maximum edit distance `n`.
 */
template <>
auto subsumes<Algorithm::TRANSPOSITION>(Position *lhs, Position *rhs,
                                        std::size_t n) -> bool;

/**
 * Returns whether `lhs` subsumes `rhs` according to the subsumption rules of
 * standard Levenshtein distance extended with the elementary operations of
 * merge and split.
 *
 * @param lhs Position to compare against `rhs`.
 * @param rhs Position to compare against `lhs`.
 * @param n Maximum edit distance to consider when matching spelling candidates.
 * @return Whether `lhs` subsumes `rhs`, given the maximum edit distance `n`.
 */
template <>
auto subsumes<Algorithm::MERGE_AND_SPLIT>(Position *lhs, Position *rhs,
                                          std::size_t n) -> bool;

} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_TRANSDUCER_SUBSUMES_H
