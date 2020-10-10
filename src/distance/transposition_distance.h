#ifndef __LIBLEVENSHTEIN__DISTANCE__TRANSPOSITION_DISTANCE_H__
#define __LIBLEVENSHTEIN__DISTANCE__TRANSPOSITION_DISTANCE_H__

#include <string>

#include "memoized_distance.h"

namespace liblevenshtein {

    class TranspositionDistance : public MemoizedDistance {
    public:
        int between(std::string v, std::string w);
    };
} // namespace liblevenshtein

#endif // __LIBLEVENSHTEIN__DISTANCE__TRANSPOSITION_DISTANCE_H__
