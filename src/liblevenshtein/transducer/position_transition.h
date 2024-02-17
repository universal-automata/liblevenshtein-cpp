#ifndef LIBLEVENSHTEIN_TRANSDUCER_POSITION_TRANSITION_H
#define LIBLEVENSHTEIN_TRANSDUCER_POSITION_TRANSITION_H

#include <cstddef>
#include <vector>

#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/position.h"

namespace liblevenshtein {

/**
 * Returns the first index of the desired character in the characteristic
 * vector, beginning at the offset \f$i\f$. The characteristic vector represents
 * a sort of moving window over the characters of the query term, and flags the
 * locations within that window whose corresponding query term characters match
 * the desired character from the dictionary term.
 *
 * @param characteristic_vector Moving window over the which query term
 * characters match the desired one from the dictionary term.
 * @param k Upper bound of the characteristic vector.
 * @param i Beginning index (offset) to seek the desired character.
 * @return The first index from the characteristic vector matching the desired
 * character.
 */
auto index_of(std::vector<bool> &characteristic_vector, std::size_t k,
              std::size_t i) -> std::size_t;

/**
 * Returns the closure over possible next Positions that are reachable from the
 * current Position by advancing the location in the dictionary by one.
 *
 * @param n Maximum edit distance to consider when matching spelling candidates.
 * @param position Current Position within the Levenshtein automaton.
 * @param characteristic_vector Moving window over matching characters of the
 * query term.
 * @param offset Where to begin examining the chracteristic_vector.
 * @return The closure over the next Positions reachable from the current
 * Position by advancing the location in the dictionary by one.
 */
template <Algorithm Type>
auto position_transition(std::size_t n, Position *position,
                         std::vector<bool> &characteristic_vector,
                         std::size_t offset) -> std::vector<Position *>;

/**
 * Returns the closure over possible next Positions that are reachable from the
 * current Position by advancing the location in the dictionary by one. This
 * covers transitions within the standard Levenshtein distance, which includes
 * the elementary operations of insertion, deletion, and substituion.
 *
 * @param n Maximum edit distance to consider when matching spelling candidates.
 * @param position Current Position within the Levenshtein automaton.
 * @param characteristic_vector Moving window over matching characters of the
 * query term.
 * @param offset Where to begin examining the chracteristic_vector.
 * @return The closure over the next Positions reachable from the current
 * Position by advancing the location in the dictionary by one.
 */
template <>
auto position_transition<Algorithm::STANDARD>(
    std::size_t n, Position *position, std::vector<bool> &characteristic_vector,
    std::size_t offset) -> std::vector<Position *>;

/**
 * Returns the closure over possible next Positions that are reachable from the
 * current Position by advancing the location in the dictionary by one. This
 * covers transitions within the standard Levenshtein distance extended with the
 * elementary operation, transposition.
 *
 * @param n Maximum edit distance to consider when matching spelling candidates.
 * @param position Current Position within the Levenshtein automaton.
 * @param characteristic_vector Moving window over matching characters of the
 * query term.
 * @param offset Where to begin examining the chracteristic_vector.
 * @return The closure over the next Positions reachable from the current
 * Position by advancing the location in the dictionary by one.
 */
template <>
auto position_transition<Algorithm::TRANSPOSITION>(
    std::size_t n, Position *position, std::vector<bool> &characteristic_vector,
    std::size_t offset) -> std::vector<Position *>;

/**
 * Returns the closure over possible next Positions that are reachable from the
 * current Position by advancing the location in the dictionary by one. This
 * covers transitions within the standard Levenshtein distance, extended with
 * the elementary operations of merge and split.
 *
 * @param n Maximum edit distance to consider when matching spelling candidates.
 * @param position Current Position within the Levenshtein automaton.
 * @param characteristic_vector Moving window over matching characters of the
 * query term.
 * @param offset Where to begin examining the chracteristic_vector.
 * @return The closure over the next Positions reachable from the current
 * Position by advancing the location in the dictionary by one.
 */
template <>
auto position_transition<Algorithm::MERGE_AND_SPLIT>(
    std::size_t n, Position *position, std::vector<bool> &characteristic_vector,
    std::size_t offset) -> std::vector<Position *>;

} // namespace liblevenshtein


#endif // LIBLEVENSHTEIN_TRANSDUCER_POSITION_TRANSITION_H
