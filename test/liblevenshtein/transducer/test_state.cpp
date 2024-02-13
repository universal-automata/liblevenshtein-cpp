#include <vector>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/comparator.h"
#include "liblevenshtein/transducer/position.h"
#include "liblevenshtein/transducer/state.h"
#include "liblevenshtein/transducer/state_iterator.h"

#include "liblevenshtein/test/utils/position_utils.h"
#include "liblevenshtein/test/types.h"

namespace ll = liblevenshtein;
namespace llt = liblevenshtein::test;

RC_GTEST_PROP(State, initializes_positions_correctly,
              (const std::vector<llt::Triple> &triples)) {
  std::vector<ll::Position *> positions = llt::to_positions(triples);
  auto *state = new ll::State(positions);
  ll::Position *actual = state->head();

  for (ll::Position *expected : positions) {
    RC_ASSERT(expected == actual);
    actual = actual->next();
  }

  delete state;
}

RC_GTEST_PROP(State, sorts_positions_correctly,
              (const std::vector<llt::Triple> &triples)) {
  RC_PRE(!triples.empty());

  std::vector<ll::Position *> positions = llt::to_positions(triples);
  auto *state = new ll::State(positions);

  state->sort(ll::compare<ll::Algorithm::STANDARD>);
  RC_ASSERT(state->head() != nullptr);
  ll::Position *prev = state->head();
  ll::Position *curr = prev->next();
  while (curr != nullptr) {
    RC_ASSERT(ll::compare<ll::Algorithm::STANDARD>(prev, curr) < 1);
    prev = curr;
    curr = curr->next();
  }

  state->sort(ll::compare<ll::Algorithm::TRANSPOSITION>);
  RC_ASSERT(state->head() != nullptr);
  prev = state->head();
  curr = prev->next();
  while (curr != nullptr) {
    RC_ASSERT(ll::compare<ll::Algorithm::TRANSPOSITION>(prev, curr) < 1);
    prev = curr;
    curr = curr->next();
  }

  state->sort(ll::compare<ll::Algorithm::MERGE_AND_SPLIT>);
  RC_ASSERT(state->head() != nullptr);
  prev = state->head();
  curr = prev->next();
  while (curr != nullptr) {
    RC_ASSERT(ll::compare<ll::Algorithm::MERGE_AND_SPLIT>(prev, curr) < 1);
    prev = curr;
    curr = curr->next();
  }

  delete state;
}

RC_GTEST_PROP(State, adds_to_tail_of_positions,
              (const std::vector<llt::Triple> &triples)) {
  std::vector<ll::Position *> positions = llt::to_positions(triples);
  auto *state = new ll::State();
  for (int i = 0; i < positions.size(); i += 1) {
    ll::Position *position = positions[i];
    state->add(position);

    ll::Position *curr = state->head();
    for (int j = 0; j <= i; j += 1) {
      RC_ASSERT(curr == positions[j]);
      curr = curr->next();
    }
  }
  delete state;
}

RC_GTEST_PROP(State, correctly_inserts_positions_after_others,
              (const std::vector<llt::Triple> &triples)) {
  std::vector<ll::Position *> positions = llt::to_positions(triples);
  auto *state = new ll::State();
  ll::Position *curr = nullptr;
  for (ll::Position *next : positions) {
      state->insert_after(curr, next);
      curr = next;
  }
  ll::Position *actual = state->head();
  for (ll::Position *expected : positions) {
      RC_ASSERT(expected == actual);
      actual = actual->next();
  }
  delete state;
}

RC_GTEST_PROP(State, correctly_removes_positions,
              (const std::vector<llt::Triple> &triples)) {
  RC_PRE(triples.size() > 2);
  std::vector<ll::Position *> positions = llt::to_positions(triples);
  auto *state = new ll::State(positions);

  ll::Position *prev = nullptr;
  ll::Position *curr = state->head();
  state->remove(prev, curr);
  RC_ASSERT(positions[1] == state->head());

  prev = state->head();
  curr = prev->next();
  state->remove(prev, curr);
  RC_ASSERT(positions[1] == state->head());

  if (positions.size() > 3) {
    RC_ASSERT(positions[3] == state->head()->next());
  } else {
    RC_ASSERT(nullptr == state->head()->next());
  }

  delete state;
}

RC_GTEST_PROP(State, iterates_over_positions,
              (const std::vector<llt::Triple> &triples)) {
  std::vector<ll::Position *> positions = llt::to_positions(triples);
  auto *state = new ll::State(positions);

  ll::StateIterator iter = state->begin();
  ll::StateIterator iter_end = state->end();

  if (triples.empty()) {
    RC_ASSERT(iter == iter_end);
  } else {
    RC_ASSERT(iter != iter_end);
    RC_ASSERT(positions[0] == *iter);

    iter.remove();
    RC_ASSERT(*iter == nullptr);

    if (triples.size() == 1) {
      RC_ASSERT(iter == iter_end);
    } else {
      RC_ASSERT(iter != iter_end);

      ++iter;
      RC_ASSERT(positions[1] == *iter);

      ++iter;
      if (triples.size() == 2) {
        RC_ASSERT(iter == iter_end);
      } else {
        RC_ASSERT(positions[2] == *iter);

        auto *position = new ll::Position(0, 0);
        iter.insert(position);
        RC_ASSERT(positions[2] == *iter);

        ++iter;
        RC_ASSERT(position == *iter);

        ++iter;
        for (int i = 3; i < triples.size(); i += 1) {
          RC_ASSERT(positions[i] == *iter);
          ++iter;
        }
      }
    }
  }

  RC_ASSERT(nullptr == *iter);
  RC_ASSERT(!(iter != iter_end));
  delete state;
}
