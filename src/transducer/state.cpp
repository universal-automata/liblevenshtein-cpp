#include "state.h"


namespace liblevenshtein {

    template <Algorithm Type>
    State<Type>* State<Type>::set_head(Position<Type>* head) {
        head->set_next(this->head);
        this->head = head;
        return this;
    }

    template <Algorithm Type>
    State<Type>* State<Type>::add(Position<Type>* next) {
        if (head == nullptr) {
            head = next;
        }
        else {
            Position<Type>* curr = head;
            while (curr->get_next()) {
                curr = curr->get_next();
            }
            curr->set_next(next);
        }
        return this;
    }

    template <Algorithm Type>
    State<Type>* State<Type>::insert_after(Position<Type> *curr, Position<Type> *next) {
        if (curr != nullptr) {
            next->set_next(curr->get_next());
            curr->set_next(next);
        }
        else {
            add(next);
        }
        return this;
    }

    template <Algorithm Type>
    State<Type>* State<Type>::remove(Position<Type> *prev, Position<Type> *curr) {
        Position<Type>* temp;
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

    template <Algorithm Type>
    Position<Type>* State<Type>::merge_sort(std::function <int(Position<Type> *, Position<Type> *)> compare,
                                Position<Type> *lhs_head) {
        if (lhs_head == nullptr || lhs_head->get_next() == nullptr) {
            return lhs_head;
        }

        Position<Type>* middle = find_middle(lhs_head);
        Position<Type>* rhs_head = middle->get_next();
        middle->set_next(nullptr);

        return merge(compare,
                     merge_sort(compare, lhs_head),
                     merge_sort(compare, rhs_head));
    }

    template <Algorithm Type>
    Position<Type>* State<Type>::merge(std::function<int(Position<Type> *, Position<Type> *)> compare,
                           Position<Type> *lhs_head, Position<Type> *rhs_head) {
        Position<Type> temp(-1, -1);
        Position<Type>* next = &temp;
        Position<Type>* curr = next;

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
        return curr;
    }

    template <Algorithm Type>
    Position<Type>* State<Type>::find_middle(Position<Type> *head) {
        Position<Type>* slow = head;
        Position<Type>* fast = head;

        while (fast->get_next() != nullptr && fast->get_next()->get_next() != nullptr) {
            slow = slow->get_next();
            fast = fast->get_next()->get_next();
        }

        return slow;
    }

    template <Algorithm Type>
    State<Type>* State<Type>::sort(std::function<int(Position<Type> *, Position<Type> *)> compare) {
        head = merge_sort(compare, head);
        return this;
    }

    template <Algorithm Type>
    StateIterator<Type> State<Type>::begin() {
        return StateIterator<Type>(this, head);
    }

    template <Algorithm Type>
    StateIterator<Type> State<Type>::end() {
        return StateIterator<Type>(this, nullptr);
    }

} // namespace liblevenshtein
