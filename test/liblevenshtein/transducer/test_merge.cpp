#include <algorithm>
#include <cstddef>
#include <vector>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "liblevenshtein/transducer/merge.h"
#include "liblevenshtein/transducer/position.h"
#include "liblevenshtein/transducer/state.h"
#include "liblevenshtein/transducer/subsumes.h"
#include "liblevenshtein/transducer/test_helpers.h"

namespace ll = liblevenshtein;


RC_GTEST_PROP(insert_after, inserts_positions_in_the_expected_location,
              (std::vector<ll::Triple> triples)) {
    std::vector<ll::Position *> positions = ll::to_positions(triples);
    ll::State *state = new ll::State();
    RC_ASSERT(state->head() == nullptr);
    ll::Position *curr = nullptr;
    for (ll::Position *next : positions) {
        ll::insert_after(state, curr, next);
        curr = next;
    }
    ll::Position *actual = state->head();
    for (ll::Position *expected : positions) {
        RC_ASSERT(expected == actual);
        actual = actual->next();
    }
    delete state;
}
