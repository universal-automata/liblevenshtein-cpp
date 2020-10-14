#ifndef __LIBLEVENSHTEIN__TRANSDUCER__STATE_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__STATE_H__

#include <functional>

#include "position.h"
#include <algorithm>


namespace liblevenshtein {

    class State {
    public:
        State* set_head(Position* head);
        State* add(Position* head);
        State* insert_after(Position* curr, Position* next);
        State* remove(Position* prev, Position* curr);
        State* sort(std::function<int(Position *, Position *)> compare);
    private:
        Position* head = nullptr;

        Position* merge_sort(std::function<int(Position *, Position *)> compare,
                             Position* lhs_head);
        Position* merge(std::function<int(Position *, Position *)> compare,
                        Position* lhs_head, Position* rhs_head);
        Position* find_middle(Position* head);
    };

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__STATE_H__
