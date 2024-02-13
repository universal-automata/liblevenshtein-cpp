#ifndef LIBLEVENSHTEIN_TRANSDUCER_ALGORITHM_H
#define LIBLEVENSHTEIN_TRANSDUCER_ALGORITHM_H


namespace liblevenshtein {

    enum class Algorithm {
        STANDARD,
        TRANSPOSITION,
        MERGE_AND_SPLIT
    };

} // namespace liblevenshtein


#endif // LIBLEVENSHTEIN_TRANSDUCER_ALGORITHM_H
