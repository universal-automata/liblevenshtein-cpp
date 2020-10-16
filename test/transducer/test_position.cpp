#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "../../src/transducer/algorithm.h"
#include "../../src/transducer/position.h"

namespace ll = liblevenshtein;


RC_GTEST_PROP(Position, has_proper_setters_and_getters,
              (const std::size_t term_index,
               const std::size_t num_errors,
               const bool position_is_special,
               const bool next_is_special)) {

    ll::Position *position = position_is_special
        ? new ll::Position(term_index, num_errors, true)
        : new ll::Position(term_index, num_errors, false);

    RC_ASSERT(nullptr == position->next());

    ll::Position *next = next_is_special
        ? new ll::Position(term_index, 1 + num_errors, true)
        : new ll::Position(term_index, 1 + num_errors, false);

    position->next(next);
    RC_ASSERT(next == position->next());

    RC_ASSERT(term_index == position->term_index());
    RC_ASSERT(num_errors == position->num_errors());
    RC_ASSERT(position_is_special == position->is_special());

    delete position;
    delete next;
}
