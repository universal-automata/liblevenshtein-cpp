#ifndef LIBLEVENSHTEIN_TRANSDUCER_STATE_ITERATOR_H
#define LIBLEVENSHTEIN_TRANSDUCER_STATE_ITERATOR_H

#include "liblevenshtein/transducer/position.h"

namespace liblevenshtein {

/** Forward declaration to avoid cyclic imports. */
class State;

/**
 * Iterates over the Position nodes in the linked-list of a Levenshtein State.
 */
class StateIterator {
public:

  /**
   * Constructs a new StateIterator of the Position nodes of `state`, with an
   * optional `outer` pointer for unsubsumption.
   *
   * @param state Levenshtein State owning the linked-list being iterated over.
   * @param head Head Position of the current sub-list.
   * @param outer Iterator during unsubsumption that owns the outermost level of
   * iteration over the linked-list.
   */
  StateIterator(State* state, Position* head, StateIterator *outer = nullptr);

  /**
   * Inserts a new Position after the current one in the linked-list.
   *
   * @param position New Position to add after the current one in the linked-list.
   */
  void insert(Position *position);

  /**
   * Removes the current Position from the linked-list.
   */
  void remove();

  /**
   * Advances the Position in the linked-list by one.
   *
   * @return A reference to the iterator containing the advanced state.
   */
  auto operator++() -> StateIterator &;

  /**
   * Returns a pointer to the current Position in the linked-list.
   *
   * @return A pointer to the current Position in the linked-list.
   */
  auto operator*() const -> Position *;

  /**
   * Returns whether this StateIterator is equivalent to another. By convention,
   * the iterators must be over the same linked-list.
   *
   * @param other A StateIterator to compare with this one for equivalence.
   * @return Whether this StateIterator is equivalent to the other.
   */
  auto operator==(const StateIterator &other) const -> bool;

private:

  /** Outermost iterator over the same linked-list, used for unsubsumption. */
  StateIterator* _outer = nullptr;

  /** Levenshtein State that owns the linked-list being iterated over. */
  State* _state = nullptr;

  /** Next Position to be iterated over. */
  Position* _next = nullptr;

  /** Current Position being iterated over. */
  Position* _curr = nullptr;

  /** Previous Position being iterated over. */
  Position* _prev = nullptr;

  /**
   * Advances the Position being iterated over by one.
   */
  void advance();
};

} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_TRANSDUCER_STATE_ITERATOR_H
