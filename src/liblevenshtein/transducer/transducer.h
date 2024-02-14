#ifndef LIBLEVENSHTEIN_TRANSDUCER_TRANSDUCER_H
#define LIBLEVENSHTEIN_TRANSDUCER_TRANSDUCER_H

#include <cstddef>
#include <string>
#include <utility>

#include "liblevenshtein/collection/dawg_node.h"
#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/intersection.h"
#include "liblevenshtein/transducer/lazy_query.h"

namespace liblevenshtein {

using Candidate = std::pair<std::string, std::size_t>;

template <Algorithm Type, class Result>
class Transducer {
public:
  Transducer(DawgNode *root);
  ~Transducer();

  auto operator()(const std::string &term, std::size_t max_distance = 2)
    -> LazyIterator<Result>;

private:
  Intersection *_intersection;
};

} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_TRANSDUCER_TRANSDUCER_H
