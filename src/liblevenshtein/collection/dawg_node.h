#ifndef LIBLEVENSHTEIN_COLLECTION_DAWG_NODE_H
#define LIBLEVENSHTEIN_COLLECTION_DAWG_NODE_H

#include <functional>
#include <map>


namespace liblevenshtein {

/**
 * Represents a position within one or more terms of a DAWG dictionary. The
 * position range from before the first character to after the last one, of each
 * term. The terms' consecutive characters are recorded as labels along the
 * edges between the nodes. The terms may be reconstructed by traversing the
 * outgoing edges from the root node of the dictionary and collecting the
 * consecutive character labels along each path. Each path constructed by
 * following the consecutive outgoing edges from the root node to final nodes
 * forms a term in the dictionary.
 */
class DawgNode {
public:

  /**
   * Constructs a new DAWG node with an optional parameter that determines
   * whether it is final (i.e. whether it is a word boundary).
   *
   * @param is_final Whether this node represents a word boundary.
   */
  DawgNode(bool is_final = false);

  /**
   * Constructs a new DAWG node with an initial mapping of outgoing edges and
   * whether it represents a word boundary.
   *
   * @param edges Mapping of outgoing edges from this node.
   * @param is_final Whether this node represents a word boundary.
   */
  DawgNode(std::map<char, DawgNode *>& edges, bool is_final = false);

  /**
   * Specifies whether this node represents a word boundary, or immediately
   * follows an edge having the final character of a dictionary term.
   *
   * @param is_final Whether this node represents a word boundary.
   **/
  void is_final(bool is_final);

  /**
   * Declares whether this node represents a word boundary, or whether it
   * immediately follows an edge having the final character of a dictionary
   * term.
   *
   * @return Whether this node represents a word boundary.
   */
  [[nodiscard]] auto is_final() const -> bool;

  /**
   * Iterates over each outgoing edge of this node and invokes a callback
   * function with each edge's character label and target node.
   *
   * @param fn Callback function to invoke with each edge's character label and
   * target node.
   */
  void for_each_edge(const std::function<void(char, DawgNode *)> &fn) const;

  /**
   * Returns the target node, following this one, along the edge annotated with
   * the given label. If no such edge exists, nullptr is returned.
   *
   * @param label Outgoing edge label whose target is desired.
   * @return Target node mapped-to from this node by the edge label, or nullptr
   * if no such target exists.
   */
  [[nodiscard]] auto transition(char label) const -> DawgNode *;

  /**
   * Adds a new outgoing edge to this node.
   *
   * @param label Annotation for the outgoing edge.
   * @param target Destination node for the outgoing edge.
   * @return This node for chaining.
   */
  auto add_edge(char label, DawgNode *target) -> DawgNode *;

  /**
   * Determines whether this node is equivalent to another.
   *
   * @param other Candidate node whose equivalence to this one is to be
   * computed.
   * @return Whether this node is equivalent to the other.
   */
  auto operator==(const DawgNode &other) const -> bool;

private:

  /** Outgoing edges from this node. */
  std::map<char, DawgNode *> _edges;

  /** Whether this node represents a word boundary. */
  bool _is_final = false;
};

} // namespace liblevenshtein

namespace std {

/**
 * Overloaded hash template struct that serves to generate hash codes for DAWG
 * nodes.
 */
template <>
struct hash<liblevenshtein::DawgNode> {

  /**
   * Generates the hash code for a DAWG node.
   *
   * @param node DAWG node whose hash code is to be generated.
   * @return Hash code for the given DAWG node.
   */
  auto operator()(const liblevenshtein::DawgNode &node) const -> size_t;
};

} // namespace std

#endif // LIBLEVENSHTEIN_COLLECTION_DAWG_NODE_H
