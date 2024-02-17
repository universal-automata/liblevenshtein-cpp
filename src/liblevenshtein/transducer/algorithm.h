#ifndef LIBLEVENSHTEIN_TRANSDUCER_ALGORITHM_H
#define LIBLEVENSHTEIN_TRANSDUCER_ALGORITHM_H

namespace liblevenshtein {

/**
 * Enumerates the available Levenshtein distance algorithms.
 */
enum class Algorithm {

  /** Standard Levenshtein distance, including the elementary operations of
  insertion, deletion, and substitution. */
  STANDARD,

  /** Standard Levenshtein distance extended with the elementary operation of
  transposition. */
  TRANSPOSITION,

  /** Standard Levenshtein distance extended with the elementary operations of
  merge and split. */
  MERGE_AND_SPLIT
};

} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_TRANSDUCER_ALGORITHM_H
