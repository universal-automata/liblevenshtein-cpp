#include <cstddef>

#include "liblevenshtein/transducer/merge.h"
#include "liblevenshtein/transducer/state_iterator.h"

namespace liblevenshtein {

void insert_after(State *state, Position *curr, Position *next) {
  if (curr == nullptr) {
    state->head(next);
  }
  else {
    state->insert_after(curr, next);
  }
}

template <>
void merge<Algorithm::STANDARD>(State *state,
                                const std::vector<Position *> &positions) {
  for (Position *a : positions) {
    std::size_t i = a->term_index();
    std::size_t e = a->num_errors();

    StateIterator iter = state->begin();
    StateIterator iter_end = state->end();
    Position *p = nullptr;

    while (iter != iter_end) {
      Position *b = *iter;
      std::size_t j = b->term_index();
      std::size_t f = b->num_errors();

      if ((e < f) || (e == f) && (i < j)) {
        p = b;
        ++iter;
      } else {
        break;
      }
    }

    if (iter != iter_end) {
      Position *b = *iter;
      std::size_t j = b->term_index();
      std::size_t f = b->num_errors();

      if ((j != i) || (f != e)) {
        insert_after(state, p, a);
      }
      else {
        delete a;
      }
    }
    else {
      insert_after(state, p, a);
    }
  }
}

template <>
void merge<Algorithm::TRANSPOSITION>(State *state,
                                     const std::vector<Position *> &positions) {
  for (Position *a : positions) {
    std::size_t i = a->term_index();
    std::size_t e = a->num_errors();
    bool s = a->is_special();

    StateIterator iter = state->begin();
    StateIterator iter_end = state->end();
    Position *p = nullptr;

    while (iter != iter_end) {
      Position *b = *iter;
      std::size_t j = b->term_index();
      std::size_t f = b->num_errors();
      bool t = b->is_special();

      if (e < f || e == f && (i < j || i == j && !s && t)) {
        p = b;
        ++iter;
      }
      else {
        break;
      }
    }

    if (iter != iter_end) {
      Position *b = *iter;
      ++iter;

      std::size_t j = b->term_index();
      std::size_t f = b->num_errors();
      bool t = b->is_special();

      if (j != i || f != e || t != s) {
        insert_after(state, p, a);
      }
      else {
        delete a;
      }
    }
    else {
      insert_after(state, p, a);
    }
  }
}

template <>
void merge<Algorithm::MERGE_AND_SPLIT>(
    State *state, const std::vector<Position *> &positions) {
  for (Position *a : positions) {
    std::size_t i = a->term_index();
    std::size_t e = a->num_errors();
    bool s = a->is_special();

    StateIterator iter = state->begin();
    StateIterator iter_end = state->end();
    Position *p = nullptr;

    while (iter != iter_end) {
      Position *b = *iter;
      std::size_t j = b->term_index();
      std::size_t f = b->num_errors();
      bool t = b->is_special();

      if (e < f || e == f && (i < j || i == j && !s && t)) {
        p = b;
        ++iter;
      }
      else {
        break;
      }
    }

    if (iter != iter_end) {
      Position *b = *iter;
      ++iter;

      std::size_t j = b->term_index();
      std::size_t f = b->num_errors();
      bool t = b->is_special();

      if (j != i || f != e || t != s) {
        insert_after(state, p, a);
      }
      else {
        delete a;
      }
    }
    else {
      insert_after(state, p, a);
    }
  }
}

} // namespace liblevenshtein
