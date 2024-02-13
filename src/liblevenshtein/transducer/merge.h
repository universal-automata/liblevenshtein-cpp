#ifndef LIBLEVENSHTEIN_TRANSDUCER_MERGE_H
#define LIBLEVENSHTEIN_TRANSDUCER_MERGE_H

#include <vector>

#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/position.h"
#include "liblevenshtein/transducer/state.h"

namespace liblevenshtein {

  void insert_after(State *state, Position *curr, Position *next);

  template <Algorithm Type>
  void merge(State *state, const std::vector<Position *> &positions);

} // namespace liblevenshtein


#endif // LIBLEVENSHTEIN_TRANSDUCER_MERGE_H
