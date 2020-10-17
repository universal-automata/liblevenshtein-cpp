#include "liblevenshtein/transducer/state_iterator.h"

namespace liblevenshtein {

    StateIterator::StateIterator(State* state, Position* head)
        : _state(state),
          _prev(nullptr),
          _curr(head),
          _next(head != nullptr ? head->next() : nullptr)
    {}

    StateIterator::StateIterator(const StateIterator &iter)
        : _state(iter._state),
          _next(iter._next),
          _curr(iter._curr),
          _prev(iter._prev)
    {}

    StateIterator::StateIterator(StateIterator &&iter) noexcept
        : _state(iter._state),
          _next(iter._next),
          _curr(iter._curr),
          _prev(iter._prev)
    {}

    StateIterator &StateIterator::operator++() {
        advance();
        return *this;
    }

    Position *StateIterator::operator*() const {
        return _curr;
    }

    bool StateIterator::operator!=(const StateIterator &other) const {
        return _curr != other._curr || _next != other._next;
    }

    bool StateIterator::operator==(const StateIterator &other) const {
        return !(*this != other);
    }

    void StateIterator::insert(Position* position) {
        if (_curr != nullptr) {
            _state->insert_after(_curr, position);
        }
        else {
            _state->head(position);
        }
        _next = position;
    }

    void StateIterator::remove() {
        if (_curr != nullptr) {
            _state->remove(_prev, _curr);
            _curr = nullptr;
        }
    }

    void StateIterator::advance() {
        if (_curr != nullptr) {
            _prev = _curr;
        }

        _curr = _next;

        if (_next != nullptr) {
            _next = _next->next();
        }
    }

} // namespace liblevenshtein
