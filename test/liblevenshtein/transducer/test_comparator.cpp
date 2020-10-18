#include <vector>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/comparator.h"
#include "liblevenshtein/transducer/position.h"
#include "liblevenshtein/transducer/test_helpers.h"

namespace ll = liblevenshtein;

RC_GTEST_PROP(Compare, correctly_compares_positions,
              (std::vector<ll::Triple> triples)) {
    std::vector<ll::Position *> positions = ll::to_positions(triples);

    if (!positions.empty()) {
        ll::Position *prev = positions[0];
        for (int i = 1; i < positions.size(); i += 1) {
            ll::Position *curr = positions[i];

            if (prev->term_index() < curr->term_index()) {
                RC_ASSERT(ll::compare<ll::Algorithm::STANDARD>(prev, curr) < 0);
                RC_ASSERT(ll::compare<ll::Algorithm::TRANSPOSITION>(prev, curr) < 0);
                RC_ASSERT(ll::compare<ll::Algorithm::MERGE_AND_SPLIT>(prev, curr) < 0);
            }
            else if (prev->term_index() > curr->term_index()) {
                RC_ASSERT(ll::compare<ll::Algorithm::STANDARD>(prev, curr) > 0);
                RC_ASSERT(ll::compare<ll::Algorithm::TRANSPOSITION>(prev, curr) > 0);
                RC_ASSERT(ll::compare<ll::Algorithm::MERGE_AND_SPLIT>(prev, curr) > 0);
            }
            else if (prev->num_errors() < curr->num_errors()) {
                RC_ASSERT(ll::compare<ll::Algorithm::STANDARD>(prev, curr) < 0);
                RC_ASSERT(ll::compare<ll::Algorithm::TRANSPOSITION>(prev, curr) < 0);
                RC_ASSERT(ll::compare<ll::Algorithm::MERGE_AND_SPLIT>(prev, curr) < 0);
            }
            else if (prev->num_errors() > curr->num_errors()) {
                RC_ASSERT(ll::compare<ll::Algorithm::STANDARD>(prev, curr) > 0);
                RC_ASSERT(ll::compare<ll::Algorithm::TRANSPOSITION>(prev, curr) > 0);
                RC_ASSERT(ll::compare<ll::Algorithm::MERGE_AND_SPLIT>(prev, curr) > 0);
            }
            else {
                RC_ASSERT(ll::compare<ll::Algorithm::STANDARD>(prev, curr) == 0);
                if (prev->is_special() && !curr->is_special()) {
                    RC_ASSERT(ll::compare<ll::Algorithm::TRANSPOSITION>(prev, curr) > 0);
                    RC_ASSERT(ll::compare<ll::Algorithm::MERGE_AND_SPLIT>(prev, curr) > 0);
                }
                else if (!prev->is_special() && curr->is_special()) {
                    RC_ASSERT(ll::compare<ll::Algorithm::TRANSPOSITION>(prev, curr) < 0);
                    RC_ASSERT(ll::compare<ll::Algorithm::MERGE_AND_SPLIT>(prev, curr) < 0);
                }
                else {
                    RC_ASSERT(ll::compare<ll::Algorithm::TRANSPOSITION>(prev, curr) == 0);
                    RC_ASSERT(ll::compare<ll::Algorithm::MERGE_AND_SPLIT>(prev, curr) == 0);
                }
            }

            prev = curr;
        }
    }

    for (ll::Position *position : positions) {
        delete position;
    }
}
