#include "state_iterator.h"


namespace liblevenshtein {

    StateIterator::StateIterator(State* state, Position* head)
        : _state(state),
          _lookahead(head)
    {}

    StateIterator::StateIterator(const StateIterator &iter)
        : _state(iter._state),
          _lookahead(iter._lookahead),
          _next(iter._next),
          _curr(iter._curr),
          _prev(iter._prev)
    {}

    StateIterator::StateIterator(StateIterator &&iter) noexcept
        : _state(iter._state),
          _lookahead(iter._lookahead),
          _next(iter._next),
          _curr(iter._curr),
          _prev(iter._prev)
    {}

    StateIterator &StateIterator::operator++() {
        if (_lookahead != nullptr) {
            _next = _lookahead;
            if (_curr != nullptr) {
                _prev = _curr;
            }
            _curr = _next;
            _lookahead = _lookahead->next();
        }
        return *this;
    }

    Position *StateIterator::operator*() const {
        return _next;
    }

    bool StateIterator::operator!=(const StateIterator &other) const {
        return _lookahead == other._lookahead;
    }

    void StateIterator::insert(Position* position) {
        if (_curr != nullptr) {
            _state->insert_after(_curr, position);
        }
        else {
            _state->head(position);
        }
        _lookahead = position;
    }

    void StateIterator::remove() {
        if (_curr != nullptr) {
            _state->remove(_prev, _curr);
            _curr = nullptr;
        }
    }

} // namespace liblevenshtein
