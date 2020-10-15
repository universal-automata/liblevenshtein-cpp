#ifndef __LIBLEVENSHTEIN__TRANSDUCER__STATE_ITERATOR_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__STATE_ITERATOR_H__

#include "algorithm.h"
#include "position.h"
#include "state.h"


namespace liblevenshtein {

    template <Algorithm Type>
    class State;

    template <Algorithm Type>
    class StateIterator {
    public:
        StateIterator(State<Type>* state, Position<Type>* head);
        StateIterator(const StateIterator<Type> &iter);
        StateIterator(StateIterator<Type> &&iter) noexcept;

        void insert(Position<Type>* position);
        void remove();

        StateIterator<Type>& operator++();
        Position<Type>* operator*() const;
        bool operator!=(const StateIterator<Type> &other) const;

      private:
        State<Type>* state;
        Position<Type>* lookahead;
        Position<Type>* next = nullptr;
        Position<Type>* curr = nullptr;
        Position<Type>* prev = nullptr;

        void advance();
    };

    template class StateIterator<Algorithm::STANDARD>;
    template class StateIterator<Algorithm::TRANSPOSITION>;
    template class StateIterator<Algorithm::MERGE_AND_SPLIT>;

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__STATE_ITERATOR_H__
