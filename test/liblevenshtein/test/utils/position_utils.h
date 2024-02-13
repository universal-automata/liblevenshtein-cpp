#ifndef LIBLEVENSHTEIN_TEST_UTILS_POSITION_UTILS_H
#define LIBLEVENSHTEIN_TEST_UTILS_POSITION_UTILS_H

#include <string>
#include <tuple>
#include <vector>

#include "liblevenshtein/transducer/position.h"

#include "liblevenshtein/test/types.h"


namespace liblevenshtein::test {

auto to_positions(const std::vector<Triple> &triples) -> std::vector<Position *>;

} // namespace liblevenshtein::test

#endif // LIBLEVENSHTEIN_TEST_UTILS_POSITION_UTILS_H
