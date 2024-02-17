#ifndef LIBLEVENSHTEIN_TRANSDUCER_UNSUBSUME_H
#define LIBLEVENSHTEIN_TRANSDUCER_UNSUBSUME_H

#include <cstddef>
#include <functional>

#include "liblevenshtein/transducer/position.h"
#include "liblevenshtein/transducer/state.h"

namespace liblevenshtein {

/** Determines whether one Position subsumes another given the maximum edit
distance to consider. */
using SubsumesFn = std::function<bool(Position *, Position *, std::size_t)>;

/**
 * Removes (unsubsumes) all Positions from a State that are subsumed by another
 * Position within the same State.
 */
class UnsubsumeFn {
public:

  /**
   * Constructs a new UnsubsumeFn that uses a SubsumesFn to filter-out subsumed
   * Positions from a State.
   *
   * @param subsumes Determines whether one Position subsumes another given the
   * maximum edit distance to consider.
   */
  UnsubsumeFn(SubsumesFn subsumes);

  /**
   * Removes (unsubsumes) all Positions from a State that are subsumed by
   * another Position within the same State.
   *
   * @param state State whose subsumed Positions are to be removed.
   * @param query_length Maximum edit distance to consider when matching
   * spelling candidates.
   */
  void operator()(State *state, std::size_t query_length);

private:

  /** Determines whether one Position subsumes another given the maximum edit
  distance to consider. */
  SubsumesFn subsumes;
};

} // namespace liblevenshtein


#endif // LIBLEVENSHTEIN_TRANSDUCER_UNSUBSUME_H
