#ifndef LIBLEVENSHTEIN_COLLECTION_PREFIX_H
#define LIBLEVENSHTEIN_COLLECTION_PREFIX_H

#include <iostream>
#include <string>

#include "liblevenshtein/collection/dawg_node.h"


namespace liblevenshtein {

/**
 * Represents the prefix of a dictionary term. The prefix is formed by
 * traversing the outgoing edges from the root node of the dictionary.
 */
class Prefix {
public:

  /**
   * Constructs a new prefix that follows another along the path from the root
   * node to the current one.
   *
   * @param node Dictionary node represented by this prefix.
   * @param parent Prefix representing the path from the root node to that
   * immediately prior to this one.
   * @param label Character label for the current position within the dictionary
   * term.
   */
  Prefix(DawgNode* node, Prefix* parent, char label);

  /**
   * Constructs the initial prefix from which all prefixes of the dictionary
   * terms follow.
   *
   * @param root Root node of the dictionary.
   */
  Prefix(DawgNode* root);

  /**
   * Copy constructor for a prefix node.
   *
   * @param prefix Prefix node to copy.
   */
  Prefix(const Prefix &prefix) = default;

  /**
   * Move constructor for a prefix node.
   *
   * @param prefix Prefix node whose memory must be moved.
   */
  Prefix(Prefix &&prefix) noexcept;

  /**
   * Returns the node analogous to this prefix, within the dictionary.
   *
   * @return Dictionary node represented by this prefix.
   */
  [[nodiscard]] auto node() const -> DawgNode *;

  /**
   * Returns the character label associated with this prefixed position within
   * the dictionary term.
   *
   * @return The character label associated with the current position within the
   * prefix of the dictionary term.
   */
  [[nodiscard]] auto label() const -> char;

  /**
   * Returns the string constructed by following the path between the root
   * prefix node and this one, which is either a prefix of the current
   * dictionary term or the whole term (which is also a prefix).
   *
   * @return The current prefix string of the dictionary term.
   */
  [[nodiscard]] auto str() const -> std::string;

  /** Specifies the ostream operator may access all this node's members. */
  friend auto operator<<(std::ostream &out, const Prefix &prefix)
      -> std::ostream &;

private:

  /** Analogous dictionary node to this prefix node. */
  DawgNode* _node;

  /** Parent prefix node to this one; used to construct the prefix string. */
  Prefix* _parent;

  /** Current character label along the path from the root prefix node to this
  one. */
  char _label;
};

} // namespace liblevenshtein


#endif // LIBLEVENSHTEIN_COLLECTION_PREFIX_H
