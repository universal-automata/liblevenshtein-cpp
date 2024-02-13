#include <utility>

#include "liblevenshtein/transducer/state_transition.h"
#include "liblevenshtein/transducer/state_iterator.h"

namespace liblevenshtein {

// NOLINTBEGIN(bugprone-easily-swappable-parameters)
StateTransition::StateTransition(PositionTransitionFn transition,
                                 CompareFn compare, MergeFn merge,
                                 UnsubsumeFn unsubsume,
                                 std::size_t max_distance,
                                 std::size_t query_length)
    // NOLINTEND(bugprone-easily-swappable-parameters)
    : transition(std::move(transition)), compare(std::move(compare)),
      merge(std::move(merge)), unsubsume(std::move(unsubsume)),
      max_distance(max_distance), query_length(query_length) {}

auto StateTransition::operator()(State *curr_state,
                                 std::vector<bool> &characteristic_vector)
    -> State * {
  std::size_t offset = curr_state->head()->term_index();
  auto *next_state = new State();
  std::size_t n = max_distance;

  for (Position *position : *curr_state) {
    merge(next_state, transition(n, position, characteristic_vector, offset));
  }

  unsubsume(next_state, query_length);

  if (next_state->head() != nullptr) {
    next_state->sort(compare);
    return next_state;
  }

  delete next_state;
  return nullptr;
}

} // namespace liblevenshtein
