#include "state.h"


namespace liblevenshtein {

    State::State(std::initializer_list<Position *> positions) {
        Position *prev = nullptr;
        for (Position *curr : positions) {
            insert_after(prev, curr);
            prev = curr;
        }
    }

    State::~State() {
        if (head != nullptr) {
            delete head;
        }
    }

    State* State::set_head(Position* head) {
        head->set_next(this->head);
        this->head = head;
        return this;
    }

    Position *State::get_head() const {
        return head;
    }

    State* State::add(Position* next) {
        if (head == nullptr) {
            head = next;
        }
        else {
            Position* curr = head;
            while (curr->get_next()) {
                curr = curr->get_next();
            }
            curr->set_next(next);
        }
        return this;
    }

    State* State::insert_after(Position *curr, Position *next) {
        if (curr != nullptr) {
            next->set_next(curr->get_next());
            curr->set_next(next);
        }
        else {
            add(next);
        }
        return this;
    }

    State* State::remove(Position *prev, Position *curr) {
        Position* temp;
        if (prev != nullptr) {
            temp = prev->get_next();
            prev->set_next(curr->get_next());
        }
        else {
            temp = head;
            head = head->get_next();
        }
        delete temp;
        return this;
    }

    Position* State::merge_sort(Comparator compare, Position *lhs_head) {
        if (lhs_head == nullptr || lhs_head->get_next() == nullptr) {
            return lhs_head;
        }

        Position* middle = find_middle(lhs_head);
        Position* rhs_head = middle->get_next();
        middle->set_next(nullptr);

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
                curr->set_next(lhs_head);
                lhs_head = lhs_head->get_next();
            }
            else {
                curr->set_next(rhs_head);
                rhs_head = rhs_head->get_next();
            }
            curr = curr->get_next();
        }

        if (rhs_head != nullptr) {
            curr->set_next(rhs_head);
        }
        else if (lhs_head != nullptr) {
            curr->set_next(lhs_head);
        }

        curr = next->get_next();
        temp.set_next(nullptr); // so the transitions aren't deleted
        return curr;
    }

    Position* State::find_middle(Position *head) {
        Position* slow = head;
        Position* fast = head;

        while (fast->get_next() != nullptr && fast->get_next()->get_next() != nullptr) {
            slow = slow->get_next();
            fast = fast->get_next()->get_next();
        }

        return slow;
    }

    State* State::sort(Comparator compare) {
        head = merge_sort(compare, head);
        return this;
    }

    StateIterator State::begin() {
        return StateIterator(this, head);
    }

    StateIterator State::end() {
        return StateIterator(this, nullptr);
    }

} // namespace liblevenshtein
