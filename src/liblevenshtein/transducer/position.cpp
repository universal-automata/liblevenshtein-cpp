#include "liblevenshtein/transducer/position.h"

namespace liblevenshtein {

    Position::Position(std::size_t term_index, std::size_t num_errors, bool is_special)
        : _term_index(term_index),
          _num_errors(num_errors),
          _is_special(is_special)
    {}

    Position::~Position() {
        if (_next != nullptr) {
            delete _next;
        }
    }

    void Position::next(Position *next) {
        _next = next;
    }

    Position *Position::next() const {
        return _next;
    }

    std::size_t Position::term_index() const {
        return _term_index;
    }

    std::size_t Position::num_errors() const {
        return _num_errors;
    }

    bool Position::is_special() const {
        return _is_special;
    }

} // namespace liblevenshtein
