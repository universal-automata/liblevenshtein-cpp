#ifndef LIBLEVENSHTEIN_TRANSDUCER_STATE_TRANSITION_H
#define LIBLEVENSHTEIN_TRANSDUCER_STATE_TRANSITION_H

#include <cstddef>
#include <functional>
#include <vector>

#include "liblevenshtein/transducer/position.h"
#include "liblevenshtein/transducer/state.h"
#include "liblevenshtein/transducer/unsubsume.h"

namespace liblevenshtein {

  using PositionTransitionFn =
    std::function<std::vector<Position *>(std::size_t, Position *,
                        std::vector<bool>&, std::size_t)>;
  using CompareFn = std::function<int(Position *, Position *)>;
  using MergeFn = std::function<void(State *, std::vector<Position *>)>;

  class StateTransition {
  public:
    StateTransition(PositionTransitionFn transition,
            CompareFn compare,
            MergeFn merge,
            UnsubsumeFn unsubsume,
            std::size_t max_distance,
            std::size_t query_length);

    auto operator()(State *curr_state, std::vector<bool> &characteristic_vector)
        -> State *;

  private:
    PositionTransitionFn transition;
    CompareFn compare;
    MergeFn merge;
    UnsubsumeFn unsubsume;
    std::size_t max_distance;
    std::size_t query_length;
  };

} // namespace liblevenshtein


#endif // LIBLEVENSHTEIN_TRANSDUCER_STATE_TRANSITION_H
