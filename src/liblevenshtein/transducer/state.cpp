#include "liblevenshtein/transducer/state.h"

namespace liblevenshtein {

    State::State(std::initializer_list<Position *> positions) {
        Position *prev = nullptr;
        for (Position *curr : positions) {
            insert_after(prev, curr);
            prev = curr;
        }
    }

    State::State(std::vector<Position *> &positions) {
        Position *prev = nullptr;
        for (Position *curr : positions) {
            insert_after(prev, curr);
            prev = curr;
        }
    }

    State::~State() {
        if (_head != nullptr) {
            delete _head;
        }
    }

    void State::head(Position* head) {
        head->next(_head);
        _head = head;
    }

    Position *State::head() const {
        return _head;
    }

    void State::add(Position* next) {
        if (_head == nullptr) {
            _head = next;
        }
        else {
            Position* curr = _head;
            while (curr->next()) {
                curr = curr->next();
            }
            curr->next(next);
        }
    }

    void State::insert_after(Position *curr, Position *next) {
        if (curr != nullptr) {
            next->next(curr->next());
            curr->next(next);
        }
        else {
            add(next);
        }
    }

    void State::remove(Position *prev, Position *curr) {
        // ASSUMPTION: prev->next() == curr
        Position* temp;
        if (prev != nullptr) {
            temp = prev->next();
            prev->next(curr->next());
        }
        else {
            temp = _head;
            _head = _head->next();
        }
        temp->next(nullptr);
        delete temp;
    }

    Position* State::merge_sort(Comparator compare, Position *lhs_head) {
        if (lhs_head == nullptr || lhs_head->next() == nullptr) {
            return lhs_head;
        }

        Position* middle = find_middle(lhs_head);
        Position* rhs_head = middle->next();
        middle->next(nullptr);

        return merge(compare,
                     merge_sort(compare, lhs_head),
                     merge_sort(compare, rhs_head));
    }

    Position* State::merge(Comparator compare, Position *lhs_head, Position *rhs_head) {
        Position temp(-1, -1);
        Position* next = &temp;
        Position* curr = next;

        while (lhs_head != nullptr && rhs_head != nullptr) {
            if (compare(lhs_head, rhs_head) < 1) {
                curr->next(lhs_head);
                lhs_head = lhs_head->next();
            }
            else {
                curr->next(rhs_head);
                rhs_head = rhs_head->next();
            }
            curr = curr->next();
        }

        if (rhs_head != nullptr) {
            curr->next(rhs_head);
        }
        else if (lhs_head != nullptr) {
            curr->next(lhs_head);
        }

        curr = next->next();
        temp.next(nullptr);
        return curr;
    }

    Position* State::find_middle(Position *head) {
        Position* slow = head;
        Position* fast = head;

        while (fast->next() != nullptr && fast->next()->next() != nullptr) {
            slow = slow->next();
            fast = fast->next()->next();
        }

        return slow;
    }

    void State::sort(Comparator compare) {
        _head = merge_sort(compare, _head);
    }

    StateIterator State::begin() {
        return StateIterator(this, _head);
    }

    StateIterator State::end() {
        return StateIterator(this, nullptr);
    }

} // namespace liblevenshtein
