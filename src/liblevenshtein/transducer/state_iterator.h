#ifndef LIBLEVENSHTEIN_TRANSDUCER_STATE_ITERATOR_H
#define LIBLEVENSHTEIN_TRANSDUCER_STATE_ITERATOR_H

#include "liblevenshtein/transducer/position.h"

namespace liblevenshtein {

  class State;

  class StateIterator {
  public:
    StateIterator(State* state, Position* head, StateIterator *parent = nullptr);

    void insert(Position *position);
    void remove();

    auto operator++() -> StateIterator &;
    auto operator*() const -> Position *;
    auto operator!=(const StateIterator &other) const -> bool;
    auto operator==(const StateIterator &other) const -> bool;

  private:
    StateIterator* _parent = nullptr;
    State* _state = nullptr;
    Position* _next = nullptr;
    Position* _curr = nullptr;
    Position* _prev = nullptr;

    void advance();
  };

} // namespace liblevenshtein


#endif // LIBLEVENSHTEIN_TRANSDUCER_STATE_ITERATOR_H
