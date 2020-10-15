#ifndef __LIBLEVENSHTEIN__TRANSDUCER__CANDIDATE_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__CANDIDATE_H__

#include <cstddef>
#include <string>


namespace liblevenshtein {

    class Candidate {
    public:
        Candidate(const std::string& term, const std::size_t distance);
        const std::string& get_term() const;
        const std::size_t get_distance() const;
    private:
        const std::string term;
        const std::size_t distance;
    };

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__CANDIDATE_H__
