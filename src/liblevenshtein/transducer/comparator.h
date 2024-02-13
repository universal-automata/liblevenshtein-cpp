#ifndef LIBLEVENSHTEIN_TRANSDUCER_COMPARATOR_H
#define LIBLEVENSHTEIN_TRANSDUCER_COMPARATOR_H

#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/position.h"

namespace liblevenshtein {

template <Algorithm Type> auto compare(Position *lhs, Position *rhs) -> int;

template <>
auto compare<Algorithm::STANDARD>(Position *lhs, Position *rhs) -> int;

template <>
auto compare<Algorithm::TRANSPOSITION>(Position *lhs, Position *rhs) -> int;

template <>
auto compare<Algorithm::MERGE_AND_SPLIT>(Position *lhs, Position *rhs) -> int;

} // namespace liblevenshtein


#endif // LIBLEVENSHTEIN_TRANSDUCER_COMPARATOR_H
