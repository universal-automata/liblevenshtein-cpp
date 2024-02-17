#ifndef LIBLEVENSHTEIN_COLLECTION_DAWG_ITERATOR_H
#define LIBLEVENSHTEIN_COLLECTION_DAWG_ITERATOR_H

#include <queue>
#include <vector>

#include "liblevenshtein/collection/dawg_node.h"
#include "liblevenshtein/collection/prefix.h"

namespace liblevenshtein {

/**
 * Iterates over all the terms in a DAWG dictionary.
 */
class DawgIterator {
public:

  /**
   * Constructs an iterator over the terms in a dictionary. Terms are yielded
   * as they are reached by traversing the consecutive outgoing edges from the
   * root node.
   *
   * @param root Root node of the dictionary.
   */
  DawgIterator(DawgNode* root);

  /**
   * Constructs an iterator representing the boundary following the final term
   * in a dictionary.
   *
   * @param term_index Size of the dictionary. Each term is enumerated from 0,
   * so when the term_index reaches the size of the dictionary, all terms have
   * been traversed.
   */
  DawgIterator(std::size_t term_index);

  /**
   * Cleans up all the prefixes allocated by this iterator.
   */
  ~DawgIterator();

  /**
   * Advances the iterator by one term.
   *
   * @return An iterator whose value is the next term in the dictionary.
   */
  auto operator++() -> DawgIterator &;

  /**
   * Returns the current dictionary term.
   *
   * @return The term at term_index of the dictionary.
   */
  auto operator*() const -> std::string;

  /**
   * Compares this iterator with one representing the boundary following the
   * final term in the dictionary. When this returns false, all terms in the
   * dictionary have been iterated over. By convention, this is only used to
   * compare iterators over the same dictionary.
   *
   * @param other An iterator whose location in the dictionary must be
   * compared with the boundary following its final term.
   * @return Whether the iterator has reached the end of the dictionary.
   */
  auto operator==(const DawgIterator &other) const -> bool;

private:

  /** Used to construct dictionary terms by collecting consecutive edge labels
  from the root node to their respective final nodes. */
  std::vector<Prefix *> _prefixes;

  /** Intermediate prefixes that have not reached all their final nodes yet. */
  std::queue<Prefix *> _pending;

  /** Value of this iterator, i.e. the current dictionary term. */
  std::string _next_value;

  /** Current index of the enumerated terms in the dictinary. */
  std::size_t _term_index = 0;

  /**
   * Advances this iterator by one term.
   */
  void advance();
};

} // namespace DawgIterator


#endif // LIBLEVENSHTEIN_COLLECTION_DAWG_ITERATOR_H
