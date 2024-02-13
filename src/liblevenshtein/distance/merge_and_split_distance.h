#ifndef LIBLEVENSHTEIN_DISTANCE_MERGE_AND_SPLIT_DISTANCE_H
#define LIBLEVENSHTEIN_DISTANCE_MERGE_AND_SPLIT_DISTANCE_H

#include <string>

#include "liblevenshtein/distance/memoized_distance.h"

namespace liblevenshtein {

  class MergeAndSplitDistance : public MemoizedDistance {
  public:
    auto between(std::string v, std::string w) -> std::size_t override;
  };

} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_DISTANCE_MERGE_AND_SPLIT_DISTANCE_H
