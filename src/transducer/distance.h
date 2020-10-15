#ifndef __LIBLEVENSHTEIN__TRANSDUCER__DISTANCE_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__DISTANCE_H__

#include <cstddef>

#include "algorithm.h"
#include "state.h"


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


#endif // __LIBLEVENSHTEIN__TRANSDUCER__DISTANCE_H__
