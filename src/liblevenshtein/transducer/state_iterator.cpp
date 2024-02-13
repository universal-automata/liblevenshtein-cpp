#include "liblevenshtein/transducer/state_iterator.h"
#include "liblevenshtein/transducer/state.h"

namespace liblevenshtein {

StateIterator::StateIterator(State* state, Position* head, StateIterator *parent)
  : _parent(parent),
    _state(state),
    _curr(head),
    _next(head != nullptr ? head->next() : nullptr)
{}

auto StateIterator::operator++() -> StateIterator & {
  advance();
  return *this;
}

auto StateIterator::operator*() const -> Position * {
  return _curr;
}

auto StateIterator::operator!=(const StateIterator &other) const -> bool {
  return _curr != other._curr || _next != other._next;
}

auto StateIterator::operator==(const StateIterator &other) const -> bool {
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
    if (_parent != nullptr && _parent->_next == _curr) {
      _parent->_next = _parent->_next->next();
    }
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
