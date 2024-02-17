#ifndef LIBLEVENSHTEIN_COLLECTION_TRANSITION_H
#define LIBLEVENSHTEIN_COLLECTION_TRANSITION_H

#include "liblevenshtein/collection/dawg_node.h"


namespace liblevenshtein {

/**
 * Represents an edge from one DawgNode to another, annotated with a character
 * label from the current position of the dictionary term.
 */
class Transition {
public:

  /**
   * Constructs a new Transition from a source DawgNode to its target, annotated
   * by the given label.
   *
   * @param label Annotation for the current Transition.
   * @param source Initial DawgNode for this Transition.
   * @param target Destination DawgNode for this Transition.
   */
  Transition(char label, DawgNode* source, DawgNode* target);

  /**
   * Copy constructor for this Transition.
   *
   * @param transition Transition to copy.
   */
  Transition(const Transition& transition) = default;

  /**
   * Move constructor for this Transition.
   *
   * @param transition Transition whose memory is to be moved to this one.
   */
  Transition(Transition&& transition) noexcept;

  /**
   * Returns the label annotating the edge from the source to the target of this
   * Transition.
   *
   * @return Annotation of this Transition.
   */
  [[nodiscard]] auto label() const -> char;

  /**
   * Returns the initial DawgNode along the edge of this transition.
   *
   * @return A pointer to the DawgNode at the beginning of this transition.
   */
  [[nodiscard]] auto source() const -> DawgNode *;

  /**
   * Returns the destination DawgNode along the edge of this transition.
   *
   * @return A pointer to the DawgNode at the ending of this transition.
   */
  [[nodiscard]] auto target() const -> DawgNode *;

  /**
   * Returns whether this Transition is equivalent to another.
   *
   * @param other A Transition whose equivalence to this one is to be
   * determined.
   * @return Whether this Transition is equivalent to another.
   */
  auto operator==(const Transition &other) const -> bool;

private:

  /** Annotation along the edge of this Transition. */
  char _label;

  /** DawgNode at the beginning of this Transition. */
  DawgNode *_source;

  /** DawgNode at the ending of this Transition. */
  DawgNode *_target;
};

} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_COLLECTION_TRANSITION_H
