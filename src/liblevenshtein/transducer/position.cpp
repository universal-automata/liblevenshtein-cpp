#include "liblevenshtein/transducer/position.h"

namespace liblevenshtein {

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
Position::Position(std::size_t term_index, std::size_t num_errors, bool is_special)
  : _term_index(term_index),
    _num_errors(num_errors),
    _is_special(is_special)
{}

Position::~Position() {
  delete _next;
}

void Position::next(Position *next) {
  _next = next;
}

auto Position::next() const -> Position * {
  return _next;
}

auto Position::term_index() const -> std::size_t {
  return _term_index;
}

auto Position::num_errors() const -> std::size_t {
  return _num_errors;
}

auto Position::is_special() const -> bool {
  return _is_special;
}

} // namespace liblevenshtein
