#ifndef LIBLEVENSHTEIN_TRANSDUCER_DISTANCE_H
#define LIBLEVENSHTEIN_TRANSDUCER_DISTANCE_H

#include <cstddef>

#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/state.h"

namespace liblevenshtein {

    template <Algorithm Type>
    std::size_t distance(State *state, std::size_t query_length);

    template <>
    std::size_t distance<Algorithm::STANDARD>(State *state,
                                              std::size_t query_length);

    template <>
    std::size_t distance<Algorithm::TRANSPOSITION>(State *state,
                                                   std::size_t query_length);

    template <>
    std::size_t distance<Algorithm::MERGE_AND_SPLIT>(State *state,
                                                     std::size_t query_length);

} // namespace liblevenshtein


#endif // LIBLEVENSHTEIN_TRANSDUCER_DISTANCE_H
