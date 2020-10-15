#ifndef __LIBLEVENSHTEIN__TRANSDUCER__STATE_TRANSITION_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__STATE_TRANSITION_H__

#include <cstddef>
#include <functional>
#include <vector>

#include "position.h"
#include "state.h"


namespace liblevenshtein {

    using TransitionFn = std::function<State*(std::size_t,Position *,std::vector<bool>&,std::size_t)>;
    using CompareFn = std::function<int(Position *, Position *)>;
    using MergeFn = std::function<void(State *, State *)>;
    using UnsubsumeFn = std::function<void(State *, std::size_t)>;

    class StateTransition {
    public:
        StateTransition(TransitionFn transition,
                        CompareFn compare,
                        MergeFn merge,
                        UnsubsumeFn unsubsume,
                        std::size_t max_distance,
                        std::size_t query_length);

        State * operator()(State *curr_state, std::vector<bool> &characteristic_vector);
    private:
        TransitionFn transition;
        CompareFn compare;
        MergeFn merge;
        UnsubsumeFn unsubsume;
        std::size_t max_distance;
        std::size_t query_length;
    };

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__STATE_TRANSITION_H__
