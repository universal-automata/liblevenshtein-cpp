#ifndef LIBLEVENSHTEIN_TRANSDUCER_POSITION_TRANSITION_H
#define LIBLEVENSHTEIN_TRANSDUCER_POSITION_TRANSITION_H

#include <cstddef>
#include <vector>

#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/position.h"

namespace liblevenshtein {

auto index_of(std::vector<bool> &characteristic_vector, std::size_t k,
              std::size_t i) -> std::size_t;

template <Algorithm Type>
auto position_transition(std::size_t n, Position *position,
                         std::vector<bool> &characteristic_vector,
                         std::size_t offset) -> std::vector<Position *>;

template <>
auto position_transition<Algorithm::STANDARD>(
    std::size_t n, Position *position, std::vector<bool> &characteristic_vector,
    std::size_t offset) -> std::vector<Position *>;

template <>
auto position_transition<Algorithm::TRANSPOSITION>(
    std::size_t n, Position *position, std::vector<bool> &characteristic_vector,
    std::size_t offset) -> std::vector<Position *>;

template <>
auto position_transition<Algorithm::MERGE_AND_SPLIT>(
    std::size_t n, Position *position, std::vector<bool> &characteristic_vector,
    std::size_t offset) -> std::vector<Position *>;

} // namespace liblevenshtein


#endif // LIBLEVENSHTEIN_TRANSDUCER_POSITION_TRANSITION_H
