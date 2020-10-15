#include <cstddef>

#include "state_iterator.h"
#include "merge.h"


namespace liblevenshtein {

    template <Algorithm Type>
    void Merge<Type>::insert_after(State *state, Position *curr, Position *next) {
        if (curr == nullptr) {
            state->set_head(next);
        }
        else {
            state->insert_after(curr, next);
        }
    }

    template <Algorithm Type>
    void Merge<Type>::operator()(State *state, State *positions) {
        for (Position *a : *positions) {
            std::size_t i = a->get_term_index();
            std::size_t e = a->get_num_errors();
            bool s = a->is_special();

            StateIterator iter = state->begin();
            StateIterator iter_end = state->end();
            Position *p = nullptr;

            while (iter != iter_end) {
                Position *b = *iter;
                std::size_t j = b->get_term_index();
                std::size_t f = b->get_num_errors();
                bool t = b->is_special();

                if (e < f || e == f && (i < j || i == j && !s && t)) {
                    p = b;
                    ++iter;
                }
                else {
                    break;
                }
            }

            if (iter != iter_end) {
                Position *b = *iter;
                ++iter;

                std::size_t j = b->get_term_index();
                std::size_t f = b->get_num_errors();
                bool t = b->is_special();

                if (j != i || f != e || t != s) {
                    insert_after(state, p, a);
                }
            }
            else {
                insert_after(state, p, a);
            }
        }
    }

    template <>
    void Merge<Algorithm::STANDARD>::operator()(State *state, State *positions) {
        for (Position *a : *positions) {
            std::size_t i = a->get_term_index();
            std::size_t e = a->get_num_errors();

            StateIterator iter = state->begin();
            StateIterator iter_end = state->end();
            Position *p = nullptr;

            while (iter != iter_end) {
                Position *b = *iter;
                std::size_t j = b->get_term_index();
                std::size_t f = b->get_num_errors();

                if (e < f || e == f && i < j) {
                    p = b;
                    ++iter;
                }
                else {
                    break;
                }
            }

            if (iter != iter_end) {
                Position *b = *iter;
                ++iter;

                std::size_t j = b->get_term_index();
                std::size_t f = b->get_num_errors();

                if (j != i || f != e) {
                    insert_after(state, p, a);
                }
            }
            else {
                insert_after(state, p, a);
            }
        }
    }

} // namespace liblevenshtein
