#ifndef LIBLEVENSHTEIN_COLLECTION_SORTED_DAWG_H
#define LIBLEVENSHTEIN_COLLECTION_SORTED_DAWG_H

#include <stack>
#include <unordered_map>
#include <unordered_set>

#include "liblevenshtein/collection/dawg.h"
#include "liblevenshtein/collection/dawg_node.h"
#include "liblevenshtein/collection/transition.h"

namespace liblevenshtein {

/**
 * A specific type of Dawg that is constructed over lexicographically sorted
 * terms. The precondition that the terms are sorted, lexigraphically, in
 * ascending order is a requirement by the algorithm used to construct this type
 * of Dawg.
 */
class SortedDawg : public Dawg {
public:
  using Dawg::Dawg;

  /**
   * Cleans up any residual intermediate members used to construct the Dawg. The
   * super destructor is subsequently called to clean up the rest of its nodes.
   */
  ~SortedDawg() override;

  /**
   * Adds a new term to this dictionary. The term must be lexicographically
   * larger than the previously added term.
   *
   * @param term A term to add to this dictionary.
   * @return Wether the term was successfully added to this dictionary.
   */
  auto add(const std::string &term) -> bool override;

  /**
   * Removes a term from this dictionary. Currently, this is just a placeholder
   * and performs no action.
   *
   * @param The term to remove from this dictionary.
   * @return Whether the term was removed from this dictionary.
   */
  auto remove(const std::string &term) -> bool override;

  /**
   * Prepares this dictionary for initialization. This function is only called
   * during initialization.
   */
  void init();

  /**
   * Cleans up any intermediate members used to initialize this Dawg.
   */
  void clean_up();

  /**
   * Specifies the dictionary has been fully initialized. This is only called
   * during initialization.
   */
  void finish();

  /**
   * Minimizes the suffixes of the unchecked paths until there are no more than
   * lower_bound unchecked transitions. This is only called during
   * initialization.
   *
   * @param lower_bound Desired size of remaining unchecked transitions once the
   * other have been minimized.
   */
  void minimize(std::size_t lower_bound);

  /**
   * Returns a DawgNode whose following suffix is equivalent to the following
   * suffix of the given DawgNode, or nullptr if none exist. This is used to
   * determine whether the given DawgNode is redundant and may be discarded.
   *
   * @param key DawgNode whose redundancy must be determined.
   * @return Either an existing DawgNode having an equivalent suffix to the key
   * or nullptr if the key is thus far unique.
   */
  auto minimized_node(DawgNode *key) const -> DawgNode *;

private:

  /** Transitions whose redundancies have not been checked. */
  std::stack<Transition> *unchecked_transitions = nullptr;

  /** Mapping of suffixes to DawgNodes that have been minimized. */
  std::unordered_map<DawgNode, DawgNode *> *minimized_nodes = nullptr;

  /** Nodes that have not been added to this Dawg. */
  std::unordered_set<DawgNode *> *floating_nodes = nullptr;

  /** Previous term inserted into this Dawg. */
  std::string _prev_term;
};

/**
 * Factory function that initializes a new SortedDawg using the terms yielded
 * from an iterator.
 *
 * @param iter Iterator that yields lexicographically sorted terms.
 * @param end Iterator representing the end of the terms.
 * @return A new SortedDawg containing all the terms from the iterator.
 */
template <class IterType>
auto sorted_dawg(IterType iter, IterType end) -> SortedDawg *;

} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_COLLECTION_SORTED_DAWG_H
