#ifndef LIBLEVENSHTEIN_DISTANCE_TRANSPOSITION_DISTANCE_H
#define LIBLEVENSHTEIN_DISTANCE_TRANSPOSITION_DISTANCE_H

#include <string>

#include "liblevenshtein/distance/memoized_distance.h"

namespace liblevenshtein::distance {

/**
 * Computes the standard Levenshtein distance extended with the elementary
 * operation of transposition. This is most useful for correcting typographic
 * errors.
 */
class TranspositionDistance : public MemoizedDistance {
public:
  auto between(std::string v, std::string w) -> std::size_t override;
};

} // namespace liblevenshtein::distance

#endif // LIBLEVENSHTEIN_DISTANCE_TRANSPOSITION_DISTANCE_H
