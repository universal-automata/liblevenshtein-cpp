#include "position.h"


namespace liblevenshtein {

    template <Algorithm Type>
    Position<Type>::Position(std::size_t term_index, std::size_t num_errors)
        : term_index(term_index),
          num_errors(num_errors)
    {}

    template <Algorithm Type>
    void Position<Type>::set_next(Position<Type> *next) {
        this->next = next;
    }

    template <Algorithm Type>
    Position<Type> *Position<Type>::get_next() const {
        return next;
    }

    template <Algorithm Type>
    std::size_t Position<Type>::get_term_index() const {
        return term_index;
    }

    template <Algorithm Type>
    std::size_t Position<Type>::get_num_errors() const {
        return num_errors;
    }

    template <>
    bool Position<Algorithm::STANDARD>::is_special() const {
        return false;
    }

    template <>
    bool Position<Algorithm::TRANSPOSITION>::is_special() const {
        return true;
    }

    template <>
    bool Position<Algorithm::MERGE_AND_SPLIT>::is_special() const {
        return true;
    }

} // namespace liblevenshtein
