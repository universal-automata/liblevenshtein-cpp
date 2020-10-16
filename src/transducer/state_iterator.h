#ifndef __LIBLEVENSHTEIN__TRANSDUCER__STATE_ITERATOR_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__STATE_ITERATOR_H__

#include "position.h"
#include "state.h"


namespace liblevenshtein {

    class State;

    class StateIterator {
    public:
        StateIterator(State* state, Position* head);
        StateIterator(const StateIterator &iter);
        StateIterator(StateIterator &&iter) noexcept;

        void insert(Position* position);
        void remove();

        StateIterator& operator++();
        Position* operator*() const;
        bool operator!=(const StateIterator &other) const;

      private:
        State* _state;
        Position* _lookahead;
        Position* _next = nullptr;
        Position* _curr = nullptr;
        Position* _prev = nullptr;
    };

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__STATE_ITERATOR_H__
