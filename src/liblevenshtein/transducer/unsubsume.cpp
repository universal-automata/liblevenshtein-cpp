#include "liblevenshtein/transducer/state_iterator.h"
#include "liblevenshtein/transducer/unsubsume.h"

namespace liblevenshtein {

    UnsubsumeFn::UnsubsumeFn(SubsumesFn subsumes)
        : subsumes(subsumes)
    {}

    void UnsubsumeFn::operator()(State *state, std::size_t query_length) {
        StateIterator outer_iter = state->begin();
        StateIterator iter_end = state->end();
        while (outer_iter != iter_end) {
            Position *outer = *outer_iter;
            std::size_t outer_errors = outer->num_errors();

            StateIterator inner_iter(state, outer, &outer_iter);
            ++inner_iter;

            while (inner_iter != iter_end) {
                Position *inner = *inner_iter;
                if (outer_errors < inner->num_errors()) {
                    break;
                }
                ++inner_iter;
            }

            while (inner_iter != iter_end) {
                Position *inner = *inner_iter;
                if (subsumes(outer, inner, query_length)) {
                    inner_iter.remove();
                }
                ++inner_iter;
            }

            ++outer_iter;
        }
    }
}
