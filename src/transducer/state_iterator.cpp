#include "state_iterator.h"


namespace liblevenshtein {

    StateIterator::StateIterator(State* state, Position* head)
        : state(state),
          lookahead(head)
    {}

    StateIterator::StateIterator(const StateIterator &iter)
        : state(iter.state),
          lookahead(iter.lookahead),
          next(iter.next),
          curr(iter.curr),
          prev(iter.prev)
    {}

    StateIterator::StateIterator(StateIterator &&iter) noexcept
        : state(iter.state),
          lookahead(iter.lookahead),
          next(iter.next),
          curr(iter.curr),
          prev(iter.prev)
    {}

    StateIterator& StateIterator::operator++() {
        advance();
        return *this;
    }

    Position* StateIterator::operator*() const {
        return next;
    }

    bool StateIterator::operator!=(const StateIterator &other) const {
        return lookahead == other.lookahead;
    }

    void StateIterator::insert(Position* position) {
        if (curr != nullptr) {
            state->insert_after(curr, position);
        }
        else {
            state->set_head(position);
        }
        lookahead = position;
    }

    void StateIterator::remove() {
        if (curr != nullptr) {
            state->remove(prev, curr);
            curr = nullptr;
        }
    }

    void StateIterator::advance() {
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
