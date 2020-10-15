#ifndef __LIBLEVENSHTEIN__TRANSDUCER__MERGE_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__MERGE_H__

#include "algorithm.h"
#include "position.h"
#include "state.h"


namespace liblevenshtein {

    template <Algorithm Type>
    class Merge {
    public:
        void operator()(State *state, State *positions);
    private:
        void insert_after(State *state, Position *curr, Position *next);
    };

    template class Merge<Algorithm::STANDARD>;
    template class Merge<Algorithm::TRANSPOSITION>;
    template class Merge<Algorithm::MERGE_AND_SPLIT>;

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__MERGE_H__
