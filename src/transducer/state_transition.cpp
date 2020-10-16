#include "state_transition.h"


namespace liblevenshtein {

    StateTransition::StateTransition(
        PositionTransitionFn transition,
        CompareFn compare,
        MergeFn merge,
        UnsubsumeFn unsubsume,
        std::size_t max_distance,
        std::size_t query_length)
        : transition(transition),
          compare(compare),
          merge(merge),
          unsubsume(unsubsume),
          max_distance(max_distance),
          query_length(query_length)
    {}

    State *
    StateTransition::operator()(State *curr_state,
                                std::vector<bool> &characteristic_vector) {
        std::size_t offset = curr_state->head()->term_index();
        State *next_state = new State();
        std::size_t n = max_distance;

        for (Position *position : *curr_state) {
            State *positions = transition(n, position, characteristic_vector, offset);
            if (positions == nullptr) {
                continue;
            }
            merge(next_state, positions);
            // delete positions;
        }

        unsubsume(next_state, query_length);

        if (next_state->head() != nullptr) {
            next_state->sort(compare);
            return next_state;
        }

        // delete next_state;
        return nullptr;
    }

} // namespace liblevenshtein
