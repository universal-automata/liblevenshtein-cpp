#ifndef __LIBLEVENSHTEIN__TRANSDUCER__ALGORITHM_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__ALGORITHM_H__


namespace liblevenshtein {

    enum class Algorithm {
        STANDARD,
        TRANSPOSITION,
        MERGE_AND_SPLIT
    };

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__ALGORITHM_H__
