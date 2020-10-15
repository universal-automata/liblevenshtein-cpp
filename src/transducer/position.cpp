#include "position.h"


namespace liblevenshtein {

    Position::Position(std::size_t term_index, std::size_t num_errors)
        : term_index(term_index),
          num_errors(num_errors)
    {}

    void Position::set_next(Position *next) {
        this->next = next;
    }

    Position *Position::get_next() const {
        return next;
    }

    std::size_t Position::get_term_index() const {
        return term_index;
    }

    std::size_t Position::get_num_errors() const {
        return num_errors;
    }

    bool Position::is_special() const {
      return false;
    }

    bool SpecialPosition::is_special() const {
        return true;
    }

} // namespace liblevenshtein
