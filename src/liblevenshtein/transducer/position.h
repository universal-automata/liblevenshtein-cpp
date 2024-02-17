#ifndef LIBLEVENSHTEIN_TRANSDUCER_POSITION_H
#define LIBLEVENSHTEIN_TRANSDUCER_POSITION_H

#include <cstddef>

namespace liblevenshtein {

/**
 * Represents a location within the Levenshtein automaton.
 */
class Position {
public:

  /**
   * Constructs a new Position within the Levenshtein automaton.
   *
   * @param term_index Current location within the dictionary term.
   * @param num_errors Accumulated number of errors at the term_index.
   * @param is_special Whether this is a special position representing an
   * extended state.
   */
  Position(std::size_t term_index, std::size_t num_errors,
           bool is_special = false);

  /**
   * Frees any owned allocations.
   */
  ~Position();

  /**
   * Assigns the subsequent Position along the current path.
   *
   * @param next The Position following this one.
   */
  void next(Position *next);

  /**
   * Returns the Position that follows this one along the current path.
   *
   * @return A pointer to the position that follows this one.
   */
  [[nodiscard]] auto next() const -> Position *;

  /**
   * Returns the current position in the dictionary term.
   *
   * @return The current position in the dictionary term.
   */
  [[nodiscard]] auto term_index() const -> std::size_t;

  /**
   * Returns the accumulated number of errors at the `term_index`.
   *
   * @return The accumulated number of errors.
   */
  [[nodiscard]] auto num_errors() const -> std::size_t;

  /**
   * Returns whether this is a special state of one of the extended algorithms.
   *
   * @return Whether this Position is special within one of the extensions.
   */
  [[nodiscard]] auto is_special() const -> bool;

private:

  /** The Position that follows this one along the current path. */
  Position *_next = nullptr;

  /** The current position within the dictionary term. */
  std::size_t _term_index;

  /** The accumulated number of errors between the spelling candidate and query
  term, at term_index of the spelling candidate. */
  std::size_t _num_errors;

  /** Whether this is a special state of one of the extended algorithms. */
  bool _is_special;
};

} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_TRANSDUCER_POSITION_H
