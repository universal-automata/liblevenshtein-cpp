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
        Position *position = new Position(0, 0);
        State *initial_state = new State({position});
        _intersection = new Intersection('\0', root, initial_state);
    }

    template <Algorithm Type, class Result>
    Transducer<Type, Result>::~Transducer() {
        delete _intersection;
    }

    template <Algorithm Type, class Result>
    LazyIterator<Result>
    Transducer<Type, Result>::operator()(const std::string &term,
                                         std::size_t max_distance) {
        return LazyIterator<Result>(
            term, max_distance, _intersection,
            StateTransition(position_transition<Type>,
                            compare<Type>,
                            merge<Type>,
                            UnsubsumeFn(subsumes<Type>),
                            max_distance, term.length()),
            distance<Type>);
    }

} // namespace liblevenshtein
