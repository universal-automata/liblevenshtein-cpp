#ifndef __LIBLEVENSHTEIN__TRANSDUCER__UNSUBSUME_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__UNSUBSUME_H__

#include <cstddef>
#include <functional>

#include "algorithm.h"
#include "position.h"
#include "state.h"
#include "subsumes.h"


namespace liblevenshtein {

    template <Algorithm Type>
    using Subsumes = std::function<bool(Position<Type> *, Position<Type> *, std::size_t)>;

    template <Algorithm Type>
    class Unsubsume {
    public:
        Unsubsume(Subsumes<Type> subsumes);
        void operator()(State<Type> *state, std::size_t query_length);
    private:
        Subsumes<Type> subsumes;
    };

    template class Unsubsume<Algorithm::STANDARD>;
    template class Unsubsume<Algorithm::TRANSPOSITION>;
    template class Unsubsume<Algorithm::MERGE_AND_SPLIT>;

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__UNSUBSUME_H__
