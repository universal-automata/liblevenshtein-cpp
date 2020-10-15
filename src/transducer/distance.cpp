#include <limits>

#include "position.h"
#include "distance.h"


namespace liblevenshtein {

    template <Algorithm Type>
    std::size_t distance(State<Type> *state, std::size_t query_length) {
        std::size_t min_distance = std::numeric_limits<std::size_t>::max();
        for (Position *position : *state) {
            if (!position->is_special()) {
                std::size_t i = position->get_term_index();
                std::size_t e = position->get_num_errors();
                std::size_t distance = query_length - i + e;
                if (distance < min_distance) {
                    min_distance = distance;
                }
            }
        }
        return min_distance;
    }

    template <>
    std::size_t distance(State<Algorithm::STANDARD> *state, std::size_t query_length) {
        std::size_t min_distance = std::numeric_limits<std::size_t>::max();
        for (Position *position : *state) {
            std::size_t i = position->get_term_index();
            std::size_t e = position->get_num_errors();
            std::size_t distance = query_length - i + e;
            if (distance < min_distance) {
                min_distance = distance;
            }
        }
        return min_distance;
    }

} // namespace liblevenshtein
