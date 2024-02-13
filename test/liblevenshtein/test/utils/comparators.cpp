#include "liblevenshtein/test/utils/comparators.h"

namespace liblevenshtein::test {

auto std_str_cmp::operator()(const std::string &lhs,
                             const std::string &rhs) const -> bool {
  return lhs < rhs;
}

} // namespace liblevenshtein::test
