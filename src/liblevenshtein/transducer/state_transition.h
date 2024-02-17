#ifndef LIBLEVENSHTEIN_TRANSDUCER_STATE_TRANSITION_H
#define LIBLEVENSHTEIN_TRANSDUCER_STATE_TRANSITION_H

#include <cstddef>
#include <functional>
#include <vector>

#include "liblevenshtein/transducer/position.h"
#include "liblevenshtein/transducer/state.h"
#include "liblevenshtein/transducer/unsubsume.h"

namespace liblevenshtein {

/** Transitions Position nodes. */
using PositionTransitionFn =
  std::function<std::vector<Position *>(std::size_t, Position *,
                      std::vector<bool>&, std::size_t)>;

/** Compares Position nodes. */
using CompareFn = std::function<int(Position *, Position *)>;

/** Merges Position nodes into a State. */
using MergeFn = std::function<void(State *, std::vector<Position *>)>;

/**
 * Transitions Levenshtein States given a characteristic vector.
 */
class StateTransition {
public:

  /**
   * Constructs a new StateTransition function.
   *
   * @param transition Maps Position nodes and characteristic vectors to
   * subsequent Position nodes.
   * @param compare Compares Position nodes.
   * @param merge Merges Positions into a State.
   * @param unsubsume Removes redundant Positions from a State according to the
   * notion of subsumption.
   * @param max_distance Maximum edit distance to consider when matching
   * spelling candidates.
   * @param query_length Length of the query term.
   */
  StateTransition(PositionTransitionFn transition,
          CompareFn compare,
          MergeFn merge,
          UnsubsumeFn unsubsume,
          std::size_t max_distance,
          std::size_t query_length);

  /**
   * Returns a successive State to the current one given the characteristic
   * vector.
   *
   * @param curr_state Current State in the Levenshtein automaton.
   * @param characteristic_vector Moving window over matching characters in the
   * query term.
   * @return The next state in the Levenshtein automaton.
   */
  auto operator()(State *curr_state, std::vector<bool> &characteristic_vector)
      -> State *;

private:

  /** Maps Position nodes and characteristic vectors to subsequent Position
  nodes. */
  PositionTransitionFn transition;

  /** Compares Position nodes. */
  CompareFn compare;

  /** Merges Positions into a State. */
  MergeFn merge;

  /** Removes redundant Positions from a State according to the notion of
  subsumption. */
  UnsubsumeFn unsubsume;

  /** Maximum edit distance to consider when matching spelling candidates. */
  std::size_t max_distance;

  /** Length of the query term. */
  std::size_t query_length;
};

} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_TRANSDUCER_STATE_TRANSITION_H
