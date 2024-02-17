#ifndef LIBLEVENSHTEIN_TRANSDUCER_MERGE_H
#define LIBLEVENSHTEIN_TRANSDUCER_MERGE_H

#include <vector>

#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/position.h"
#include "liblevenshtein/transducer/state.h"

namespace liblevenshtein {

/**
 * Inserts one Position after another.
 *
 * @param state Levenshtein State whose positions are being merged.
 * @param curr Position whose follow Position is being updated.
 * @param next Position to insert after curr.
 */
void insert_after(State *state, Position *curr, Position *next);

/**
 * Merges a list of Positions into the Levenshtein state. This operation greatly
 * speeds up the matching of spelling candidates.
 *
 * @param state Levenshtein State whose positions are to be merged with the
 * others.
 * @param positions Positions to merge into the State.
 */
template <Algorithm Type>
void merge(State *state, const std::vector<Position *> &positions);

} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_TRANSDUCER_MERGE_H
