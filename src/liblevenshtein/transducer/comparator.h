#ifndef __LIBLEVENSHTEIN__TRANSDUCER__COMPARATOR_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__COMPARATOR_H__

#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/position.h"

namespace liblevenshtein {

    template <Algorithm Type>
    int compare(Position* lhs, Position *rhs);

    template <> int compare<Algorithm::STANDARD>(Position *lhs, Position *rhs);
    template <> int compare<Algorithm::TRANSPOSITION>(Position *lhs, Position *rhs);
    template <> int compare<Algorithm::MERGE_AND_SPLIT>(Position *lhs, Position *rhs);

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__COMPARATOR_H__
