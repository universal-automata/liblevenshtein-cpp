#ifndef __LIBLEVENSHTEIN__TRANSDUCER__STATE_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__STATE_H__

#include <functional>

#include "algorithm.h"
#include "position.h"
#include "state_iterator.h"


namespace liblevenshtein {

    template <Algorithm Type>
    using Comparator = std::function<int(Position<Type> *, Position<Type> *)>;

    template <Algorithm Type>
    class StateIterator;

    template <Algorithm Type>
    class State {
    public:
        State<Type> *set_head(Position<Type> *head);
        State<Type> *add(Position<Type> *head);
        State<Type> *insert_after(Position<Type> *curr, Position<Type> *next);
        State<Type> *remove(Position<Type> *prev, Position<Type> *curr);
        State<Type> *sort(Comparator<Type> compare);

        StateIterator<Type> begin();
        StateIterator<Type> end();

      private:
        Position<Type> *head = nullptr;

        Position<Type> *merge_sort(Comparator<Type> compare, Position<Type> *lhs_head);
        Position<Type> *merge(Comparator<Type> compare, Position<Type> *lhs_head, Position<Type> *rhs_head);
        Position<Type> *find_middle(Position<Type> *head);
    };

    template class State<Algorithm::STANDARD>;
    template class State<Algorithm::TRANSPOSITION>;
    template class State<Algorithm::MERGE_AND_SPLIT>;

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__STATE_H__
