#include "state_iterator.h"
#include "unsubsume.h"


namespace liblevenshtein {

    template <Algorithm Type>
    Unsubsume<Type>::Unsubsume(Subsumes<Type> subsumes)
        : subsumes(subsumes)
    {}

    template <Algorithm Type>
    void Unsubsume<Type>::operator()(State<Type> *state, std::size_t query_length) {
        StateIterator<Type> outer_iter = state->begin();
        StateIterator<Type> iter_end = state->end();
        while (outer_iter != iter_end) {
            Position<Type> *outer = *outer_iter;
            ++outer_iter;

            std::size_t outer_errors = outer->get_num_errors();

            StateIterator<Type> inner_iter = outer_iter; // copy
            while (inner_iter != iter_end) {
                Position<Type> *inner = *inner_iter;
                if (outer_errors < inner->get_num_errors()) {
                    break;
                }
                ++inner_iter;
            }

            while (inner_iter != iter_end) {
                Position<Type> *inner = *inner_iter;
                ++inner_iter;

                if (subsumes(outer, inner, query_length)) {
                    inner_iter.remove();
                }
            }
        }
    }
}
