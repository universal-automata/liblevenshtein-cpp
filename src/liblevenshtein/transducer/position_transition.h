#ifndef __LIBLEVENSHTEIN__TRANSDUCER__POSITION_TRANSITION_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__POSITION_TRANSITION_H__

#include <cstddef>
#include <vector>

#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/position.h"
#include "liblevenshtein/transducer/state.h"

namespace liblevenshtein {

    std::size_t index_of(std::vector<bool> &characteristic_vector,
                         std::size_t k, std::size_t i);

    template <Algorithm Type>
    State *position_transition(std::size_t n, Position *position,
                               std::vector<bool> &characteristic_vector,
                               std::size_t offset);

    template <>
    State *position_transition<Algorithm::STANDARD>(
        std::size_t n, Position *position,
        std::vector<bool> &characteristic_vector,
        std::size_t offset);

    template <>
    State *position_transition<Algorithm::TRANSPOSITION>(
        std::size_t n, Position *position,
        std::vector<bool> &characteristic_vector, std::size_t offset);

    template <>
    State *position_transition<Algorithm::MERGE_AND_SPLIT>(
        std::size_t n, Position *position,
        std::vector<bool> &characteristic_vector, std::size_t offset);

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__POSITION_TRANSITION_H__
