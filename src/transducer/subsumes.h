#ifndef __LIBLEVENSHTEIN__TRANSDUCER__SUBSUMES_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__SUBSUMES_H__

#include "algorithm.h"
#include "position.h"


namespace liblevenshtein {

    template <Algorithm Type>
    bool subsumes(Position<Type> * lhs, Position<Type> *rhs, std::size_t n);

    template <>
    bool subsumes(Position<Algorithm::STANDARD> *lhs,
                  Position<Algorithm::STANDARD> *rhs,
                  std::size_t n);

    template <>
    bool subsumes(Position<Algorithm::TRANSPOSITION> *lhs,
                  Position<Algorithm::TRANSPOSITION> *rhs,
                  std::size_t n);

    template <>
    bool subsumes(Position<Algorithm::MERGE_AND_SPLIT> *lhs,
                  Position<Algorithm::MERGE_AND_SPLIT> *rhs,
                  std::size_t n);

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__SUBSUMES_H__
