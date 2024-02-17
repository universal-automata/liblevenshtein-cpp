#ifndef LIBLEVENSHTEIN_COLLECTION_DAWG_H
#define LIBLEVENSHTEIN_COLLECTION_DAWG_H

#include <iostream>
#include <string>
#include <unordered_set>

#include "liblevenshtein/collection/dawg_iterator.h"
#include "liblevenshtein/collection/dawg_node.h"

namespace liblevenshtein {

  /**
   * A Directed Acyclic Word Graph (DAWG) maps sequences of characters to form
   * words; the collection of words is known as a dictionary. As its name
   * implies, it is a directed, acyclic automaton having a single root node from
   * which all terms in the dictionary are reachable. It is important that only
   * those terms in the dictionary may be formed by traversing the edges of the
   * DAWG, no terms that are not in the dictionary may be formed by joining
   * subsequent outgoing edges from the root. Nodes denoting word boundaries are
   * flagged as being final.
   */
class Dawg {
public:

  /**
   * Constructs a new DAWG with the given root node and number of dictionary
   * terms (size). The number of terms reachable by combining the subsequent
   * outgoing edges from the root must be equal to the size.
   *
   * @param root Node from which all dictionary terms may be reached by
   * subsequently traversing its outgoing edges.
   * @param size Number of terms in the dictionary.
   */
  Dawg(DawgNode* root, std::size_t size);

  /**
   * Constructs an empty DAWG with a default root node (there are no outgoing
   * edges or reachable terms from the root, not even the empty string).
   */
  Dawg();

  /**
   * Deletes all the nodes associated with this dictionary.
   */
  virtual ~Dawg();

  /**
   * Adds a new term to this dictionary by adding missing sequential edges
   * leading outward from the root node.
   *
   * @param term The term to add to this dictionary.
   * @return Whether the term was successfully added to this dictionary.
   */
  virtual auto add(const std::string &term) -> bool = 0;

  /**
   * Removes a term from this dictionary and cleans up its path.
   *
   * @param term The term to remove from this dictionary.
   * @return Whether the term was removed from this dictionary.
   */
  virtual auto remove(const std::string &term) -> bool = 0;

  /**
   * Determines whether the given term is contained within this dictionary.
   *
   * @param term Query term whose membership in this dictionary must be
   * determined.
   * @return Whether the term is contained within this dictionary.
   */
  [[nodiscard]] auto contains(const std::string &term) const -> bool;

  /**
   * Returns a pointer to the root node of this dictionary from which all its
   * terms may be determined.
   *
   * @return A pointer to the root node of this dictionary.
   */
  [[nodiscard]] auto root() const -> DawgNode *;

  /**
   * Returns the number of terms in this dictionary.
   *
   * @return The size of this dictionary.
   */
  [[nodiscard]] auto size() const -> size_t;

  /**
   * Returns an iterator pointing to the first term in this dictionary, from
   * which all terms may be iterated over.
   *
   * @return An iterator pointing to the first term in this dictionary.
   */
  [[nodiscard]] auto begin() const -> DawgIterator;

  /**
   * Returns an iterator representing the boundary following the final term in
   * this dictionary. The value of the iterator is not a term, but represent a
   * boundary that must not be crossed.
   *
   * @return An iterator pointing to the boundary following the final term in
   * this dictionary.
   */
  [[nodiscard]] auto end() const -> DawgIterator;

  /**
   * Determines whether another DAWG is equivalent to this one.
   *
   * @param other Dictionary (DAWG) to compare to this one.
   * @return Whether the other dictionary is equivalent to this one.
   */
  auto operator==(const Dawg &other) const -> bool;

  /** Specifies the hash function for this DAWG may view its membership. */
  friend class std::hash<Dawg>;

  /** Specifies the output streaming operator for this DAWG may view its
  membership. */
  friend auto operator<<(std::ostream &out, const Dawg &dawg)
      -> std::ostream &;

protected:

  /** Root node of this DAWG from which all its terms may be reached. */
  DawgNode* _root;

  /** Number of terms reachable from the root node. */
  std::size_t _size;

  /**
   * Returns a set of all nodes reachable from the root, including the root.
   *
   * @return The closure of nodes reachable from the root, including the root.
   */
  [[nodiscard]] auto all_nodes() const -> std::unordered_set<DawgNode *>;
};

} // namespace liblevenshtein


namespace std {

/**
 * Generates a hash code for the given DAWG.
 *
 * @param dawg Dictionary whose hash code should be generated.
 * @return The generated hash code for the parameterized DAWG.
 */
template <>
struct hash<liblevenshtein::Dawg> {

  /**
   * Generates a hash code for the given DAWG.
   *
   * @param dawg DAWG whose hash code is to be generated.
   * @return The hash code for the given DAWG.
   */
  auto operator()(const liblevenshtein::Dawg &dawg) const -> size_t;
};
} // namespace std


#endif // LIBLEVENSHTEIN_COLLECTION_DAWG_H
