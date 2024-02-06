#ifndef __LIBLEVENSHTEIN__TRANSDUCER__TRANSDUCER_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__TRANSDUCER_H__

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "liblevenshtein/collection/dawg.h"
#include "liblevenshtein/collection/dawg_node.h"
#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/intersection.h"
#include "liblevenshtein/transducer/lazy_query.h"
#include "liblevenshtein/transducer/state.h"

namespace liblevenshtein {

    using Candidate = std::pair<std::string, std::size_t>;

    template <Algorithm Type, class Result>
    class Transducer {
    public:
        Transducer(DawgNode *root);
        ~Transducer();

        LazyIterator<Result> operator()(const std::string& term, std::size_t max_distance=2);
    private:
        Intersection *_intersection;
    };

} // namespace liblevenshtein

#endif // __LIBLEVENSHTEIN__TRANSDUCER__TRANSDUCER_H__
