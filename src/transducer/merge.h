#ifndef __LIBLEVENSHTEIN__TRANSDUCER__MERGE_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__MERGE_H__

#include "algorithm.h"
#include "position.h"
#include "state.h"


namespace liblevenshtein {

    void insert_after(State *state, Position *curr, Position *next);

    template <Algorithm Type>
    void merge(State *state, State *positions);

    template <>
    void merge<Algorithm::STANDARD>(State *state, State *positions);

    template <>
    void merge<Algorithm::TRANSPOSITION>(State *state, State *positions);

    template <>
    void merge<Algorithm::MERGE_AND_SPLIT>(State *state, State *positions);

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__MERGE_H__
