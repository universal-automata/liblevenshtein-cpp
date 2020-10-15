#ifndef __LIBLEVENSHTEIN__TRANSDUCER__STATE_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__STATE_H__

#include <functional>

#include "algorithm.h"
#include "position.h"
#include "state_iterator.h"


namespace liblevenshtein {

    template <Algorithm Type>
    using Comparator = std::function<int(Position *, Position *)>;

    template <Algorithm Type>
    class StateIterator;

    template <Algorithm Type>
    class State {
    public:
        State<Type> *set_head(Position *head);
        State<Type> *add(Position *head);
        State<Type> *insert_after(Position *curr, Position *next);
        State<Type> *remove(Position *prev, Position *curr);
        State<Type> *sort(Comparator<Type> compare);

        StateIterator<Type> begin();
        StateIterator<Type> end();

      private:
        Position *head = nullptr;

        Position *merge_sort(Comparator<Type> compare, Position *lhs_head);
        Position *merge(Comparator<Type> compare, Position *lhs_head, Position *rhs_head);
        Position *find_middle(Position *head);
    };

    template class State<Algorithm::STANDARD>;
    template class State<Algorithm::TRANSPOSITION>;
    template class State<Algorithm::MERGE_AND_SPLIT>;

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__STATE_H__
