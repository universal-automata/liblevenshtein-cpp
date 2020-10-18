#include "liblevenshtein/transducer/test_helpers.h"


namespace liblevenshtein {

    bool std_str_cmp::operator()(const std::string &lhs, const std::string &rhs) const {
        return lhs < rhs;
    }

    std::vector<Position *> to_positions(std::vector<Triple> &triples) {
        std::vector<Position *> positions;
        for (const Triple &triple : triples) {
            positions.push_back(new Position(std::get<0>(triple), std::get<1>(triple), std::get<2>(triple)));
        }
        return positions;
    }

} // namespace liblevenshtein
