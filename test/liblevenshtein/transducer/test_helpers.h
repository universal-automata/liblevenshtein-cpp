#ifndef __LIBLEVENSHTEIN__TRANSDUCER__TEST_HELPERS_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__TEST_HELPERS_H__

#include <string>
#include <tuple>
#include <vector>

#include "liblevenshtein/transducer/position.h"


namespace liblevenshtein {

    using Triple = std::tuple<std::size_t, std::size_t, bool>;

    std::vector<Position *> to_positions(std::vector<Triple> &triples);

    struct std_str_cmp {
        bool operator()(const std::string &lhs, const std::string &rhs) const;
    };

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__TEST__HELPERS_H__
