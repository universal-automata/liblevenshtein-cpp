#ifndef LIBLEVENSHTEIN_TRANSDUCER_INTERSECTION_H
#define LIBLEVENSHTEIN_TRANSDUCER_INTERSECTION_H

#include <iostream>
#include <string>

#include "liblevenshtein/collection/dawg_node.h"
#include "liblevenshtein/transducer/state.h"

namespace liblevenshtein {

/**
 * Represents an Intersection between a dictionary automaton and Levenshtein
 * automaton, guided by the query term.
 */
class Intersection {
public:

  /**
   * Constructs a new Intersection between a dictionary automaton and
   * Levenshtein automaton, guided by the query term.
   *
   * @param label Transition annotation from the outgoing edge to the given DawgNode.
   * @param node Placeholder in the dictionary automaton.
   * @param state Levenshtein transducer State.
   * @param parent The preceding Intersection node along the current path.
   */
  Intersection(char label, DawgNode *node, State *state, Intersection *parent = nullptr);

  /**
   * Frees all owned members.
   */
  ~Intersection();

  /**
   * Returns the dictionary DawgNode from the Intersection.
   *
   * @return Dictionary node from the Intersection.
   */
  [[nodiscard]] auto node() const -> DawgNode *;

  /**
   * Returns the Levenshtein State from the Intersection.
   *
   * @return The Levenshtein State from the Intersection.
   */
  [[nodiscard]] auto state() const -> State *;

  /**
   * Concatenates all subsequent character labels from the Intersection nodes
   * beginning at the root of the dictionary up to here.
   *
   * @return Prefix of the current dictionary term that ends at this
   * Intersection node.
   */
  [[nodiscard]] auto str() const -> std::string;

  /** Specifies the ostream operator may access all the members. */
  friend auto operator<<(std::ostream &out, const Intersection &intersection)
      -> std::ostream &;

private:

  /** Transition annotation from the outgoing edge to the given DawgNode. */
  char _label;

  /** Placeholder in the dictionary automaton. */
  DawgNode *_node;

  /** Levenshtein transducer State. */
  State *_state;

  /** The preceding Intersection node along the current path. */
  Intersection *_parent;
};

} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_TRANSDUCER_INTERSECTION_H
