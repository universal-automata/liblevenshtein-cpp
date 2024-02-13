#include "liblevenshtein/transducer/transducer.h"
#include "liblevenshtein/transducer/comparator.h"
#include "liblevenshtein/transducer/distance.h"
#include "liblevenshtein/transducer/merge.h"
#include "liblevenshtein/transducer/position.h"
#include "liblevenshtein/transducer/position_transition.h"
#include "liblevenshtein/transducer/state_transition.h"
#include "liblevenshtein/transducer/subsumes.h"
#include "liblevenshtein/transducer/unsubsume.h"

namespace liblevenshtein {

template <Algorithm Type, class Result>
Transducer<Type, Result>::Transducer(DawgNode *root) {
  auto *position = new Position(0, 0);
  auto *initial_state = new State({position});
  _intersection = new Intersection('\0', root, initial_state);
}

template <Algorithm Type, class Result>
Transducer<Type, Result>::~Transducer() {
  delete _intersection;
}

template <Algorithm Type, class Result>
auto Transducer<Type, Result>::operator()(const std::string &term,
                                          std::size_t max_distance)
    -> LazyIterator<Result> {
  return LazyIterator<Result>(
    term, max_distance, _intersection,
    StateTransition(position_transition<Type>, compare<Type>,
            merge<Type>, UnsubsumeFn(subsumes<Type>),
            max_distance, term.length()),
    distance<Type>);
}

template class Transducer<Algorithm::STANDARD, std::string>;
template class Transducer<Algorithm::STANDARD, Candidate>;
template class Transducer<Algorithm::TRANSPOSITION, std::string>;
template class Transducer<Algorithm::TRANSPOSITION, Candidate>;
template class Transducer<Algorithm::MERGE_AND_SPLIT, std::string>;
template class Transducer<Algorithm::MERGE_AND_SPLIT, Candidate>;

} // namespace liblevenshtein
