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
        ? new ll::SpecialPosition(term_index, num_errors)
        : new ll::Position(term_index, num_errors);

    RC_ASSERT(nullptr == position->get_next());

    ll::Position *next = next_is_special
        ? new ll::SpecialPosition(term_index, 1 + num_errors)
        : new ll::Position(term_index, 1 + num_errors);

    position->set_next(next);
    RC_ASSERT(next == position->get_next());

    RC_ASSERT(term_index == position->get_term_index());
    RC_ASSERT(num_errors == position->get_num_errors());
    RC_ASSERT(position_is_special == position->is_special());

    delete position;
    delete next;
}
