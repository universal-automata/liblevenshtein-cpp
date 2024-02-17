#ifndef LIBLEVENSHTEIN_TRANSDUCER_STATE_H
#define LIBLEVENSHTEIN_TRANSDUCER_STATE_H

#include <functional>
#include <initializer_list>
#include <vector>

#include "liblevenshtein/transducer/position.h"

namespace liblevenshtein {

using Comparator = std::function<int(Position *, Position *)>;

/** Forward declaration to avoid cyclic imports. */
class StateIterator;

/**
 * Consists of a closure of Position nodes within the Levenshtein automaton.
 * Each State consists of all possible locations that are reachable within the
 * intersection of the Levenshtein and dictionary automata, guided by the query
 * term, at the current index within the dictionary.
 */
class State {
public:

  /**
   * Constructs an empty state, which is most commonly used to represent the
   * intersection of the root nodes of the Levenshtein and dictionary automata.
   */
  State() = default;

  /**
   * Constructs a new State with an initial list of Positions.
   *
   * @param positions Initial list of Positions at the current index within the
   * dictionary automaton.
   */
  State(std::initializer_list<Position *> positions);

  /**
   * Constructs a new State with an initial list of Positions.
   *
   * @param positions Initial list of Positions at the current index within the
   * dictionary automaton.
   */
  State(std::vector<Position *> &positions);

  /**
   * Frees any owned allocations.
   */
  ~State();

  /**
   * Sets the first element in the linked-list of Position nodes. The
   * linked-list is used with a modified version of merge-sort to merge new
   * Positions that will not be redundant.
   *
   * @param head First Position in the linked-list of Positions.
   */
  void head(Position *head);

  /**
   * Returns the first Position in the linked-list of Position nodes.
   *
   * @return The first Position in the linked-list of Position nodes.
   */
  [[nodiscard]] auto head() const -> Position *;

  /**
   * Adds a new Position to the tail of the linked-list.
   *
   * @param next The Position to insert at the tail of the linked-list.
   */
  void add(Position *next);

  /**
   * Inserts a new Position into the linked-list following an existing member.
   *
   * @param curr Existing member of the linked-list whose follow node should be
   * set to next.
   * @param next New Position to insert into the linked-list following curr.
   */
  void insert_after(Position *curr, Position *next);

  /**
   * Removes a Position from the linked-list. By convention, prev must be the
   * immediately preceding Position in the linked-list to curr.
   *
   * @param prev Position in the linked-list preceding the one to remove.
   * @param curr Position in the linked-lsit to remove.
   */
  void remove(Position *prev, Position *curr);

  /**
   * Merge-sorts the linked-list of Positions.
   *
   * @param compare Comparator to use during sortation.
   */
  void sort(const Comparator &compare);

  /**
   * Returns an iterator over the Positions in this State, beginning at the head
   * and traversing to the tail.
   *
   * @return An iterator over Positions in this State.
   */
  auto begin() -> StateIterator;

  /**
   * Returns an iterator representing the end of the linked-list of Positions.
   *
   * @return An iterator pointing to the end of the linked-list.
   */
  auto end() -> StateIterator;

private:

  /** First Position in the linked-list. This will be the lexicographically
  least Position in the linked-list. Each successive Position is
  lexicographically greater than the previous ones. */
  Position* _head = nullptr;

  /**
   * Sorts the linked-list of Positions within the Levenshtein automaton.
   *
   * @param compare Algorithm-specific comparator for sorting the linked-list of
   * Position nodes.
   * @param lower Lower bound of linked-list nodes for the current branch of
   * sortation.
   * @return A pointer to the head of the sorted sub-list.
   */
  auto merge_sort(const Comparator &compare, Position *lower) -> Position *;

  /**
   * Merge-sorts the nodes in the range between `lower` and `upper`.
   *
   * @param compare Comparator used to lexicographically sort the Position
   * nodes.
   * @param lower Lower bound of sortation.
   * @param upper Upper bound of sortation.
   * @return A pointer to the head of the sorted sub-list.
   */
  static auto merge(const Comparator &compare, Position *lower, Position *upper)
      -> Position *;

  /**
   * Finds the middle node between `lower` and the tail.
   *
   * @param lower Lower bound for the search for the mid-point.
   * @return A pointer to the mid-point between `lower` and the tail.
   */
  static auto find_middle(Position *lower) -> Position *;
};

} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_TRANSDUCER_STATE_H
