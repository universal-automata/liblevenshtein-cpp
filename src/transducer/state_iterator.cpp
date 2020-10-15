#include "state_iterator.h"


namespace liblevenshtein {

    template <Algorithm Type>
    StateIterator<Type>::StateIterator(State<Type>* state, Position<Type>* head)
        : state(state),
          lookahead(head)
    {}

    template <Algorithm Type>
    StateIterator<Type>::StateIterator(const StateIterator<Type> &iter)
        : state(iter.state),
          lookahead(iter.lookahead),
          next(iter.next),
          curr(iter.curr),
          prev(iter.prev)
    {}

    template <Algorithm Type>
    StateIterator<Type>::StateIterator(StateIterator<Type> &&iter) noexcept
        : state(iter.state),
          lookahead(iter.lookahead),
          next(iter.next),
          curr(iter.curr),
          prev(iter.prev)
    {}

    template <Algorithm Type>
    StateIterator<Type> &StateIterator<Type>::operator++() {
        advance();
        return *this;
    }

    template <Algorithm Type>
    Position<Type> *StateIterator<Type>::operator*() const {
        return next;
    }

    template <Algorithm Type>
    bool StateIterator<Type>::operator!=(const StateIterator<Type> &other) const {
        return lookahead == other.lookahead;
    }

    template <Algorithm Type>
    void StateIterator<Type>::insert(Position<Type>* position) {
        if (curr != nullptr) {
            state->insert_after(curr, position);
        }
        else {
            state->set_head(position);
        }
        lookahead = position;
    }

    template <Algorithm Type>
    void StateIterator<Type>::remove() {
        if (curr != nullptr) {
            state->remove(prev, curr);
            curr = nullptr;
        }
    }

    template <Algorithm Type>
    void StateIterator<Type>::advance() {
        if (lookahead != nullptr) {
            next = lookahead;
            if (curr != nullptr) {
                prev = curr;
            }
            curr = next;
            lookahead = lookahead->get_next();
        }
    }

} // namespace liblevenshtein
