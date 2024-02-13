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

using TransitionFn = std::function<State *(State *, std::vector<bool> &)>;
using DistanceFn = std::function<std::size_t(State *, std::size_t)>;

template <class Result> class LazyQuery {
public:
  LazyQuery(const std::string &term, std::size_t max_distance,
            Intersection *intersection, TransitionFn transition,
            DistanceFn min_distance);

  LazyQuery() = default;
  ~LazyQuery();

  auto operator++() -> LazyQuery &;
  auto operator*() const -> const Result &;
  auto operator!=(const LazyQuery &other) const -> bool;

private:
  std::queue<Intersection *> _pending;
  std::queue<std::pair<char, DawgNode *>> _edges;
  std::vector<Intersection *> _intersections;

  bool _is_complete = false;
  Intersection *_intersection = nullptr;
  Result _candidate;

  std::string _term;
  std::size_t _max_distance;
  TransitionFn transition;
  DistanceFn min_distance;

  std::size_t _a;
  std::size_t _k;
  std::size_t _i;

  void advance();

  void update_candidate(std::string &term, std::size_t distance);

  auto build_intersection(char label, DawgNode *node, State *state,
                          Intersection *parent) -> Intersection *;

  auto characteristic_vector(char x, std::string &term, std::size_t k,
                             std::size_t i) -> std::vector<bool>;
};

template <class Result> class LazyIterator {
public:
  LazyIterator(const std::string &term, std::size_t max_distance,
               Intersection *intersection, TransitionFn transition,
               DistanceFn min_distance);

  auto begin() -> LazyQuery<Result>;
  auto end() -> LazyQuery<Result>;

private:
  std::string _term;
  std::size_t _max_distance;
  Intersection *_intersection;
  TransitionFn transition;
  DistanceFn min_distance;
};

} // namespace liblevenshtein


#endif // LIBLEVENSHTEIN_TRANSDUCER_LAZY_QUERY_H
