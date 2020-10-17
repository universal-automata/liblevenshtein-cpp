#include <cstddef>
#include <tuple>
#include <vector>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "../../src/transducer/position.h"
#include "../../src/transducer/state.h"
#include "../../src/transducer/merge.h"

namespace ll = liblevenshtein;


using Triple = std::tuple<std::size_t, std::size_t, bool>;


std::vector<ll::Position *> to_positions(std::vector<Triple> &triples) {
    std::vector<ll::Position *> positions;
    for (const Triple &triple : triples) {
        positions.push_back(new ll::Position(
            std::get<0>(triple), std::get<1>(triple), std::get<2>(triple)));
    }
    return positions;
}


RC_GTEST_PROP(insert_after, inserts_positions_in_the_expected_location,
              (std::vector<Triple> triples)) {
    std::vector<ll::Position *> positions = to_positions(triples);
    ll::State *state = new ll::State();
    RC_ASSERT(state->head() == nullptr);
    ll::Position *curr = nullptr;
    for (ll::Position *next : positions) {
        ll::insert_after(state, curr, next);
    }
    ll::Position *actual = state->head();
    for (ll::Position *expected : positions) {
        RC_ASSERT(expected == actual);
        actual = actual->next();
    }
    delete state;
}
