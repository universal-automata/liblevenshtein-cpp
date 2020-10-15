#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "../../src/transducer/algorithm.h"
#include "../../src/transducer/position.h"

namespace ll = liblevenshtein;


RC_GTEST_PROP(StandardPosition, has_proper_setters_and_getters,
              (const std::size_t term_index,
               const std::size_t num_errors)) {
    ll::Position<ll::Algorithm::STANDARD> *position =
        new ll::Position<ll::Algorithm::STANDARD>(term_index, num_errors);

    RC_ASSERT(nullptr == position->get_next());

    ll::Position<ll::Algorithm::STANDARD> *next =
        new ll::Position<ll::Algorithm::STANDARD>(term_index, num_errors);
    position->set_next(next);
    RC_ASSERT(next == position->get_next());

    RC_ASSERT(term_index == position->get_term_index());
    RC_ASSERT(num_errors == position->get_num_errors());
    RC_ASSERT(!position->is_special());

    delete position;
    delete next;
}


RC_GTEST_PROP(TranspositionPosition, has_proper_setters_and_getters,
              (const std::size_t term_index,
               const std::size_t num_errors)) {
    ll::Position<ll::Algorithm::TRANSPOSITION> *position =
        new ll::Position<ll::Algorithm::TRANSPOSITION>(term_index, num_errors);

    RC_ASSERT(nullptr == position->get_next());

    ll::Position<ll::Algorithm::TRANSPOSITION> *next =
        new ll::Position<ll::Algorithm::TRANSPOSITION>(term_index, num_errors);
    position->set_next(next);
    RC_ASSERT(next == position->get_next());

    RC_ASSERT(term_index == position->get_term_index());
    RC_ASSERT(num_errors == position->get_num_errors());
    RC_ASSERT(position->is_special());

    delete position;
    delete next;
}


RC_GTEST_PROP(MergeAndSplitPosition, has_proper_setters_and_getters,
              (const std::size_t term_index, const std::size_t num_errors)) {
    ll::Position<ll::Algorithm::MERGE_AND_SPLIT> *position =
        new ll::Position<ll::Algorithm::MERGE_AND_SPLIT>(term_index, num_errors);

    RC_ASSERT(nullptr == position->get_next());

    ll::Position<ll::Algorithm::MERGE_AND_SPLIT> *next =
        new ll::Position<ll::Algorithm::MERGE_AND_SPLIT>(term_index, num_errors);
    position->set_next(next);
    RC_ASSERT(next == position->get_next());

    RC_ASSERT(term_index == position->get_term_index());
    RC_ASSERT(num_errors == position->get_num_errors());
    RC_ASSERT(position->is_special());

    delete position;
    delete next;
}
