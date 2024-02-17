#ifndef LIBLEVENSHTEIN_TRANSDUCER_LAZY_QUERY_H
#define LIBLEVENSHTEIN_TRANSDUCER_LAZY_QUERY_H

#include <cstddef>
#include <functional>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include "liblevenshtein/collection/dawg_node.h"
#include "liblevenshtein/transducer/intersection.h"
#include "liblevenshtein/transducer/state.h"

namespace liblevenshtein {

/** Returns the Levenshtein State mapped-to by another State and characteristic
vector. */
using TransitionFn = std::function<State *(State *, std::vector<bool> &)>;

/** Infers the Levenshtein distance from a final Levenshtein State and the
length of the query term. */
using DistanceFn = std::function<std::size_t(State *, std::size_t)>;

/**
 * Lazily traverses the intersection between the dictionary automaton and
 * Levenshtein automaton, guided by the query term, and yields each spelling
 * candidate as it is matched.
 */
template <class Result> class LazyQuery {
public:

  /**
   * Constructs a new LazyQuery which yields spelling candidates as they are
   * matched while traversing the intersection between the dictionary automaton
   * and Levenshtein automaton, guided by the query term.
   *
   * @param term Query term whose spelling candidates are to be matched.
   * @param max_distance Maximum edit distance to consider when matching
   * spelling candidates.
   * @param intersection Initial Intersection between the root node of the
   * dictionary and the initial Levenshtein State.
   * @param transition Function that maps one Levenshtein State to another with
   * input from a characteristic vector.
   * @param min_distance Infers the Levenshtein distance between the query term
   * and a spelling candidate.
   */
  LazyQuery(const std::string &term, std::size_t max_distance,
            Intersection *intersection, TransitionFn transition,
            DistanceFn min_distance);

  /**
   * Constructs a LazyQuery that represents the end of the spelling candidates.
   */
  LazyQuery() = default;

  /**
   * Frees any owned members.
   */
  ~LazyQuery();

  /**
   * Advances to the next spelling candidate.
   *
   * @return An advanced LazyQuery that points to the next spelling candidate.
   */
  auto operator++() -> LazyQuery &;

  /**
   * Returns the current spelling candidate.
   *
   * @return The current spelling candidate.
   */
  auto operator*() const -> const Result &;

  /**
   * Returns whether this LazyQuery has matched all the spelling candidates.
   *
   * @param other An ignored instance of LazyQuery.
   * @return Whether all the spelling candidates have been matched.
   */
  auto operator==(const LazyQuery &other) const -> bool;

private:

  /** Intermediate Intersection instances representing paths along the
  intersection between the dictionary automaton and Levenshtein automaton,
  guided by the query term. */
  std::queue<Intersection *> _pending;

  /** Outgoing dictionary node edges that are pending traversal along the
  intersection between the dictionary automaton and Levenshtein automaton,
  guided by the query term. */
  std::queue<std::pair<char, DawgNode *>> _edges;

  /** Tracks Intersection allocations so they may be freed. */
  std::vector<Intersection *> _intersections;

  /** Whether all the spelling candidates have been matched. */
  bool _is_complete = false;

  /** Current whose respective spelling candidates are being considered. */
  Intersection *_intersection = nullptr;

  /** Presently matched spelling candidate. */
  Result _candidate;

  /** Query term whose spelling candidates are to be matched. */
  std::string _term;

  /** Maximum edit distance to consider when matching spelling candidates. */
  std::size_t _max_distance;

  /** Maps one Levenshtein State to another given the State and a characteristic
  vector. */
  TransitionFn transition;

  /** Infers the Levenshtein distance between the query term and a spelling
  candidate. */
  DistanceFn min_distance;

  /** Intermediate value used to compare edit distances without overflowing. */
  std::size_t _a;

  /** Intermediate value used to compare edit distances without overflowing. */
  std::size_t _k;

  /** Intermediate value used to compare edit distances without overflowing. */
  std::size_t _i;

  /**
   * Advances to the next spelling candidate.
   */
  void advance();

  /**
   * Sets the current spelling candidate according to the desired Result type.
   *
   * @param term Spelling candidate.
   * @param distance Levenshtein distance between the query term and the
   * spelling candidate.
   */
  void update_candidate(std::string &term, std::size_t distance);

  /**
   * Factory function that constructs and records a new Intersection instance.
   *
   * @param label The character annotating the incoming edge of the current
   * dictionary node in the traversal.
   * @param node The current dictionary node in the traversal.
   * @param state The current Levenshtein State in the traversal.
   * @param parent The immediately preceding Intersection node used to
   * reconstruct the spelling candidate.
   * @return A new Intersection with the given parameters.
   */
  auto build_intersection(char label, DawgNode *node, State *state,
                          Intersection *parent) -> Intersection *;

  /**
   * Flags all instances of the given character in the query term within a
   * window of consecutive characters.
   *
   * @param x Character from the dictionary automaton to match within the window
   * over the characters in the query term.
   * @param term Query term.
   * @param k Window size of the characteristic vector.
   * @param i Base offset of the window for the characteristic vector.
   * @return The characteristic vector containing matched characters within the
   * desired window over the consecutive characters of the query term.
   */
  auto characteristic_vector(char x, std::string &term, std::size_t k,
                             std::size_t i) -> std::vector<bool>;
};

/**
 * Lazily traverses the intersection between the dictionary automaton and
 * Levenshtein automaton, guided by the query term, and yields each spelling
 * candidate as it is matched.
 */
template <class Result> class LazyIterator {
public:

  /**
   * Constructs a new LazyIterator which yields spelling candidates as they are
   * matched while traversing the intersection between the dictionary automaton
   * and Levenshtein automaton, guided by the query term.
   *
   * @param term Query term whose spelling candidates are to be matched.
   * @param max_distance Maximum edit distance to consider when matching
   * spelling candidates.
   * @param intersection Initial Intersection between the root node of the
   * dictionary and the initial Levenshtein State.
   * @param transition Function that maps one Levenshtein State to another with
   * input from a characteristic vector.
   * @param min_distance Infers the Levenshtein distance between the query term
   * and a spelling candidate.
   */
  LazyIterator(const std::string &term, std::size_t max_distance,
               Intersection *intersection, TransitionFn transition,
               DistanceFn min_distance);

  /**
   * Returns an instance of LazyQuery that yields spelling candidates of the
   * given Type.
   *
   * @return An iterator over the spelling candidates for the query term.
   */
  auto begin() -> LazyQuery<Result>;

  /**
   * Returns a placeholder representing the end of the spelling candidates.
   *
   * @return A boundary representing the end of the spelling candidates.
   */
  auto end() -> LazyQuery<Result>;

private:

  /** Query term whose spelling candidates are to be matched. */
  std::string _term;

  /** Maximum edit distance to consider when matching spelling candidates. */
  std::size_t _max_distance;

  /** Initial Intersection between the dictionary root node and initial
  Levenshtein State. */
  Intersection *_intersection;

  /** Maps one Levenshtein State to another given the state and a characteristic
  vector. */
  TransitionFn transition;

  /** Infers the Levenshtein distance between the query term and a spelling
  candidate. */
  DistanceFn min_distance;
};

} // namespace liblevenshtein


#endif // LIBLEVENSHTEIN_TRANSDUCER_LAZY_QUERY_H
