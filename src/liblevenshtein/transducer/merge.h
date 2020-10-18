#ifndef __LIBLEVENSHTEIN__TRANSDUCER__MERGE_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__MERGE_H__

#include <vector>

#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/position.h"
#include "liblevenshtein/transducer/state.h"

namespace liblevenshtein {

    void insert_after(State *state, Position *curr, Position *next);

    template <Algorithm Type>
    void merge(State *state, std::vector<Position *> positions);

    template <>
    void merge<Algorithm::STANDARD>(State *state, std::vector<Position *> positions);

    template <>
    void merge<Algorithm::TRANSPOSITION>(State *state, std::vector<Position *> positions);

    template <>
    void merge<Algorithm::MERGE_AND_SPLIT>(State *state, std::vector<Position *> positions);

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__MERGE_H__
