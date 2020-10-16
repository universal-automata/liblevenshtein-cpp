#include "position.h"
#include "position_transition.h"
#include "state_transition.h"
#include "distance.h"
#include "comparator.h"
#include "merge.h"
#include "unsubsume.h"
#include "subsumes.h"
#include "transducer.h"


namespace liblevenshtein {

    template <Algorithm Type, class Result>
    Transducer<Type, Result>::Transducer(DawgNode *root)
        : _root(root),
          _initial_state(new State({new Position(0, 0)}))
    {}

    template <Algorithm Type, class Result>
    Transducer<Type, Result>::~Transducer() {
        delete _initial_state;
    }

    template <>
    LazyIterator<std::string>
    Transducer<Algorithm::STANDARD, std::string>::operator()(
        std::string &term, std::size_t max_distance) {
        return LazyIterator<std::string>(
            term, max_distance, _root, _initial_state,
            StateTransition(position_transition<Algorithm::STANDARD>,
                            compare<Algorithm::STANDARD>,
                            merge<Algorithm::STANDARD>,
                            UnsubsumeFn(subsumes<Algorithm::STANDARD>),
                            max_distance, term.length()),
            distance<Algorithm::STANDARD>);
    }

    template <>
    LazyIterator<Candidate>
    Transducer<Algorithm::STANDARD, Candidate>::operator()(
        std::string &term, std::size_t max_distance) {
        return LazyIterator<Candidate>(
            term, max_distance, _root, _initial_state,
            StateTransition(position_transition<Algorithm::STANDARD>,
                            compare<Algorithm::STANDARD>,
                            merge<Algorithm::STANDARD>,
                            UnsubsumeFn(subsumes<Algorithm::STANDARD>),
                            max_distance, term.length()),
            distance<Algorithm::STANDARD>);
    }

    template <>
    LazyIterator<std::string>
    Transducer<Algorithm::TRANSPOSITION, std::string>::operator()(
        std::string &term, std::size_t max_distance) {
        return LazyIterator<std::string>(
            term, max_distance, _root, _initial_state,
            StateTransition(position_transition<Algorithm::TRANSPOSITION>,
                            compare<Algorithm::TRANSPOSITION>,
                            merge<Algorithm::TRANSPOSITION>,
                            UnsubsumeFn(subsumes<Algorithm::TRANSPOSITION>),
                            max_distance, term.length()),
            distance<Algorithm::TRANSPOSITION>);
    }

    template <>
    LazyIterator<Candidate>
    Transducer<Algorithm::TRANSPOSITION, Candidate>::operator()(
        std::string &term, std::size_t max_distance) {
        return LazyIterator<Candidate>(
            term, max_distance, _root, _initial_state,
            StateTransition(position_transition<Algorithm::TRANSPOSITION>,
                            compare<Algorithm::TRANSPOSITION>,
                            merge<Algorithm::TRANSPOSITION>,
                            UnsubsumeFn(subsumes<Algorithm::TRANSPOSITION>),
                            max_distance, term.length()),
            distance<Algorithm::TRANSPOSITION>);
    }

    template <>
    LazyIterator<std::string>
    Transducer<Algorithm::MERGE_AND_SPLIT, std::string>::operator()(
        std::string &term, std::size_t max_distance) {
        return LazyIterator<std::string>(
            term, max_distance, _root, _initial_state,
            StateTransition(position_transition<Algorithm::MERGE_AND_SPLIT>,
                            compare<Algorithm::MERGE_AND_SPLIT>,
                            merge<Algorithm::MERGE_AND_SPLIT>,
                            UnsubsumeFn(subsumes<Algorithm::MERGE_AND_SPLIT>),
                            max_distance, term.length()),
            distance<Algorithm::MERGE_AND_SPLIT>);
    }

    template <>
    LazyIterator<Candidate>
    Transducer<Algorithm::MERGE_AND_SPLIT, Candidate>::operator()(
        std::string &term, std::size_t max_distance) {
        return LazyIterator<Candidate>(
            term, max_distance, _root, _initial_state,
            StateTransition(position_transition<Algorithm::MERGE_AND_SPLIT>,
                            compare<Algorithm::MERGE_AND_SPLIT>,
                            merge<Algorithm::MERGE_AND_SPLIT>,
                            UnsubsumeFn(subsumes<Algorithm::MERGE_AND_SPLIT>),
                            max_distance, term.length()),
            distance<Algorithm::MERGE_AND_SPLIT>);
    }

} // namespace liblevenshtein
