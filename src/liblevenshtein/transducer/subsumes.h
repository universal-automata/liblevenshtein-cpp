#ifndef LIBLEVENSHTEIN_TRANSDUCER_SUBSUMES_H
#define LIBLEVENSHTEIN_TRANSDUCER_SUBSUMES_H

#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/position.h"

namespace liblevenshtein {

template <Algorithm Type>
auto subsumes(Position *lhs, Position *rhs, std::size_t n) -> bool;

template <>
auto subsumes<Algorithm::STANDARD>(Position *lhs, Position *rhs, std::size_t n)
    -> bool;

template <>
auto subsumes<Algorithm::TRANSPOSITION>(Position *lhs, Position *rhs,
                                        std::size_t n) -> bool;

template <>
auto subsumes<Algorithm::MERGE_AND_SPLIT>(Position *lhs, Position *rhs,
                                          std::size_t n) -> bool;

} // namespace liblevenshtein


#endif // LIBLEVENSHTEIN_TRANSDUCER_SUBSUMES_H
