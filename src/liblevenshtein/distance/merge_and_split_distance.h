#ifndef __LIBLEVENSHTEIN__DISTANCE__MERGE_AND_SPLIT_DISTANCE_H__
#define __LIBLEVENSHTEIN__DISTANCE__MERGE_AND_SPLIT_DISTANCE_H__

#include <string>

#include "liblevenshtein/distance/memoized_distance.h"

namespace liblevenshtein {

    class MergeAndSplitDistance : public MemoizedDistance {
    public:
        int between(std::string v, std::string w);
    };

} // namespace liblevenshtein

#endif // __LIBLEVENSHTEIN__DISTANCE__MERGE_AND_SPLIT_DISTANCE_H__
