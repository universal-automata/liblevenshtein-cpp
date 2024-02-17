#ifndef LIBLEVENSHTEIN_TRANSDUCER_COMPARATOR_H
#define LIBLEVENSHTEIN_TRANSDUCER_COMPARATOR_H

#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/position.h"

namespace liblevenshtein {

/**
 * Compares two Positions within the Levenshtein transducer.
 *
 * @param lhs First Position to compare.
 * @param rhs Second Position to compare.
 * @return A negative value if \f$lhs < rhs\f$, a positive value if \f$lhs >
 * rhs\f$, or zero if \f$lhs = rhs\f$.
 */
template <Algorithm Type> auto compare(Position *lhs, Position *rhs) -> int;

/**
 * Compares two Positions for the standard Levenshtein transducer.
 *
 * @param lhs First Position to compare.
 * @param rhs Second Position to compare.
 * @return A negative value if \f$lhs < rhs\f$, a positive value if \f$lhs >
 * rhs\f$, or zero if \f$lhs = rhs\f$.
 */
template <>
auto compare<Algorithm::STANDARD>(Position *lhs, Position *rhs) -> int;

/**
 * Compares two Positions for the standard Levenshtein transducer extended with
 * transposition.
 *
 * @param lhs First Position to compare.
 * @param rhs Second Position to compare.
 * @return A negative value if \f$lhs < rhs\f$, a positive value if \f$lhs >
 * rhs\f$, or zero if \f$lhs = rhs\f$.
 */
template <>
auto compare<Algorithm::TRANSPOSITION>(Position *lhs, Position *rhs) -> int;

/**
 * Compares two Positions for the standard Levenshtein transducer extended with
 * merge and split.
 *
 * @param lhs First Position to compare.
 * @param rhs Second Position to compare.
 * @return A negative value if \f$lhs < rhs\f$, a positive value if \f$lhs >
 * rhs\f$, or zero if \f$lhs = rhs\f$.
 */
template <>
auto compare<Algorithm::MERGE_AND_SPLIT>(Position *lhs, Position *rhs) -> int;

} // namespace liblevenshtein


#endif // LIBLEVENSHTEIN_TRANSDUCER_COMPARATOR_H
