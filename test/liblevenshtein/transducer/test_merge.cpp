#include <vector>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "liblevenshtein/transducer/merge.h"
#include "liblevenshtein/transducer/position.h"
#include "liblevenshtein/transducer/state.h"

#include "liblevenshtein/test/utils/position_utils.h"
#include "liblevenshtein/test/types.h"

namespace ll = liblevenshtein;
namespace llt = liblevenshtein::test;


RC_GTEST_PROP(insert_after, inserts_positions_in_the_expected_location,
              (const std::vector<llt::Triple> &triples)) {
    std::vector<ll::Position *> positions = llt::to_positions(triples);
    auto *state = new ll::State();
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
