#ifndef LIBLEVENSHTEIN_TRANSDUCER_DISTANCE_H
#define LIBLEVENSHTEIN_TRANSDUCER_DISTANCE_H

#include <cstddef>

#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/state.h"

namespace liblevenshtein {

/**
 * Infers the Levenshtein distance from the given State and query length.
 *
 * @param state Levenshtein transducer final State from which we may infer the
 * respective distance.
 * @param query_length Length of the query term which is necessary for inferring
 * the distance from the given State.
 * @return The Levenshtein distance from the given State and query length.
 */
template <Algorithm Type>
auto distance(State *state, std::size_t query_length) -> std::size_t;

/**
 * Infers the Levenshtein distance from the given State and query length for the
 * standard Levenshtein distance, which includes the elementary operations of
 * insertion, deletion, and substitution.
 *
 * @param state Levenshtein transducer final State from which we may infer the
 * respective distance.
 * @param query_length Length of the query term which is necessary for inferring
 * the distance from the given State.
 * @return The Levenshtein distance from the given State and query length.
 */
template <>
auto distance<Algorithm::STANDARD>(State *state, std::size_t query_length)
    -> std::size_t;

/**
 * Infers the Levenshtein distance from the given State and query length for the
 * standard Levenshtein distance extended with the elementary operation of
 * transposition.
 *
 * @param state Levenshtein transducer final State from which we may infer the
 * respective distance.
 * @param query_length Length of the query term which is necessary for inferring
 * the distance from the given State.
 * @return The Levenshtein distance from the given State and query length.
 */
template <>
auto distance<Algorithm::TRANSPOSITION>(State *state, std::size_t query_length)
    -> std::size_t;


/**
 * Infers the Levenshtein distance from the given State and query length for the
 * standard Levenshtein distance extended with the elementary operations of
 * merge and split.
 *
 * @param state Levenshtein transducer final State from which we may infer the
 * respective distance.
 * @param query_length Length of the query term which is necessary for inferring
 * the distance from the given State.
 * @return The Levenshtein distance from the given State and query length.
 */
template <>
auto distance<Algorithm::MERGE_AND_SPLIT>(State *state,
                                          std::size_t query_length)
    -> std::size_t;

} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_TRANSDUCER_DISTANCE_H
