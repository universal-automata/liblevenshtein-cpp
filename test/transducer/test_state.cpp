#include <cstddef>
#include <tuple>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "../../src/transducer/algorithm.h"
#include "../../src/transducer/comparator.h"
#include "../../src/transducer/position.h"
#include "../../src/transducer/state.h"
#include "../../src/transducer/state_iterator.h"

namespace ll = liblevenshtein;

using Triple = std::tuple<std::size_t, std::size_t, bool>;


std::vector<ll::Position *> to_positions(std::vector<Triple> &triples) {
    std::vector<ll::Position *> positions;
    for (const Triple& triple : triples) {
        positions.push_back(new ll::Position(
            std::get<0>(triple), std::get<1>(triple), std::get<2>(triple)));
    }
    return positions;
}


RC_GTEST_PROP(State, initializes_positions_correctly, (std::vector<Triple> triples)) {
    std::vector<ll::Position *> positions = to_positions(triples);
    ll::State *state = new ll::State(positions);
    ll::Position *actual = state->head();

    for (ll::Position *expected : positions) {
        RC_ASSERT(expected == actual);
        actual = actual->next();
    }

    delete state;
}


RC_GTEST_PROP(State, sorts_positions_correctly, (std::vector<Triple> triples)) {
    RC_PRE(!triples.empty());

    std::vector<ll::Position *> positions = to_positions(triples);
    ll::State *state = new ll::State(positions);

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

RC_GTEST_PROP(State, adds_to_tail_of_positions, (std::vector<Triple> triples)) {
    std::vector<ll::Position *> positions = to_positions(triples);
    ll::State *state = new ll::State();
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
              (std::vector<Triple> triples)) {
  std::vector<ll::Position *> positions = to_positions(triples);
  ll::State *state = new ll::State();
  ll::Position *prev = nullptr;
  for (ll::Position *curr : positions) {
      state->insert_after(prev, curr);
      prev = curr;
  }
  ll::Position *actual = state->head();
  for (ll::Position *expected : positions) {
      RC_ASSERT(expected == actual);
      actual = actual->next();
  }
  delete state;
}

RC_GTEST_PROP(State, correctly_removes_positions,
              (std::vector<Triple> triples)) {
    RC_PRE(triples.size() > 2);
    std::vector<ll::Position *> positions = to_positions(triples);
    ll::State *state = new ll::State(positions);

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
    }
    else {
        RC_ASSERT(nullptr == state->head()->next());
    }

    delete state;
}

RC_GTEST_PROP(State, iterates_over_positions,
              (std::vector<Triple> triples)) {
    std::vector<ll::Position *> positions = to_positions(triples);
    ll::State *state = new ll::State(positions);

    ll::StateIterator iter = state->begin();
    ll::StateIterator iter_end = state->end();

    if (triples.empty()) {
        RC_ASSERT(iter == iter_end);
    }
    else {
        RC_ASSERT(iter != iter_end);
        RC_ASSERT(positions[0] == *iter);

        iter.remove();
        RC_ASSERT(*iter == nullptr);

        if (triples.size() == 1) {
            RC_ASSERT(iter == iter_end);
        }
        else {
            RC_ASSERT(iter != iter_end);

            ++iter;
            RC_ASSERT(positions[1] == *iter);

            ++iter;
            if (triples.size() == 2) {
                RC_ASSERT(iter == iter_end);
            }
            else {
                RC_ASSERT(positions[2] == *iter);

                ll::Position *position = new ll::Position(0, 0);
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
