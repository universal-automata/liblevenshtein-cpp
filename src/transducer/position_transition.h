#ifndef __LIBLEVENSHTEIN__TRANSDUCER__POSITION_TRANSITION_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__POSITION_TRANSITION_H__

#include <cstddef>
#include <vector>

#include "algorithm.h"
#include "position.h"
#include "state.h"


namespace liblevenshtein {

    template <Algorithm Type>
    class PositionTransition {
    public:
        State *operator()(std::size_t n,
                          Position *position,
                          std::vector<bool> &characteristic_vector,
                          std::size_t offset);
    private:
        std::size_t index_of(std::vector<bool> &characteristic_vector,
                             std::size_t k,
                             std::size_t i);
    };

    template class PositionTransition<Algorithm::STANDARD>;
    template class PositionTransition<Algorithm::TRANSPOSITION>;
    template class PositionTransition<Algorithm::MERGE_AND_SPLIT>;

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__POSITION_TRANSITION_H__
