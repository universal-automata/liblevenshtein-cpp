#ifndef LIBLEVENSHTEIN_TEST_UTILS_COMPARATORS_H
#define LIBLEVENSHTEIN_TEST_UTILS_COMPARATORS_H

#include <string>
#include <tuple>
#include <vector>

#include "liblevenshtein/transducer/position.h"


namespace liblevenshtein::test {

struct std_str_cmp {
  auto operator()(const std::string &lhs, const std::string &rhs) const -> bool;
};

} // namespace liblevenshtein::test

#endif // LIBLEVENSHTEIN_TEST_UTILS_COMPARATORS_H
