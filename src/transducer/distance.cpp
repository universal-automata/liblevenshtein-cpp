#include <cstdint>
#include <stdint.h>

#include "position.h"
#include "distance.h"


namespace liblevenshtein {

    template <>
    std::size_t distance<Algorithm::STANDARD>(State *state,
                                              std::size_t query_length) {
        std::size_t min_distance = SIZE_MAX;
        for (Position *position : *state) {
            std::size_t i = position->term_index();
            std::size_t e = position->num_errors();
            std::size_t distance = query_length - i + e;
            if (distance < min_distance) {
                min_distance = distance;
            }
        }
        return min_distance;
    }

    template <>
    std::size_t distance<Algorithm::TRANSPOSITION>(State *state, std::size_t query_length) {
        std::size_t min_distance = SIZE_MAX;
        for (Position *position : *state) {
            if (!position->is_special()) {
                std::size_t i = position->term_index();
                std::size_t e = position->num_errors();
                std::size_t distance = query_length - i + e;
                if (distance < min_distance) {
                    min_distance = distance;
                }
            }
        }
        return min_distance;
    }

    template <>
    std::size_t distance<Algorithm::MERGE_AND_SPLIT>(State *state, std::size_t query_length) {
        std::size_t min_distance = SIZE_MAX;
        for (Position *position : *state) {
            if (!position->is_special()) {
                std::size_t i = position->term_index();
                std::size_t e = position->num_errors();
                std::size_t distance = query_length - i + e;
                if (distance < min_distance) {
                    min_distance = distance;
                }
            }
        }
        return min_distance;
    }

} // namespace liblevenshtein
