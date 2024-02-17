#ifndef LIBLEVENSHTEIN_DISTANCE_MERGE_AND_SPLIT_DISTANCE_H
#define LIBLEVENSHTEIN_DISTANCE_MERGE_AND_SPLIT_DISTANCE_H

#include <string>

#include "liblevenshtein/distance/memoized_distance.h"

namespace liblevenshtein::distance {

/**
 * Computes the standard Levenshtein distance extended with two additional
 * elementary operations: (1) merge and (2) split. This is most useful for
 * correcting OCR errors (optical character recognition).
 */
class MergeAndSplitDistance : public MemoizedDistance {
public:

  auto between(std::string v, std::string w) -> std::size_t override;
};

} // namespace liblevenshtein::distance

#endif // LIBLEVENSHTEIN_DISTANCE_MERGE_AND_SPLIT_DISTANCE_H
