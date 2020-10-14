#ifndef __LIBLEVENSHTEIN__TRANSDUCER__SUBSUMES_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__SUBSUMES_H__

#include "algorithm.h"
#include "position.h"


namespace liblevenshtein {

    template <Algorithm algorithm>
    bool subsumes(Position* lhs, Position* rhs, std::size_t n);

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__SUBSUMES_H__
