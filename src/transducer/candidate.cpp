#include "candidate.h"


namespace liblevenshtein {

    Candidate::Candidate(const std::string& term, const std::size_t distance)
        : term(term),
          distance(distance)
    {}

    const std::string& Candidate::get_term() const {
        return term;
    }

    const std::size_t Candidate::get_distance() const {
        return distance;
    }

} //namespace liblevenshtein
