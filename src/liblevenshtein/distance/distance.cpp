#include "liblevenshtein/distance/distance.h"

namespace liblevenshtein::distance {

auto Distance::operator()(const std::string &v, const std::string &w)
    -> std::size_t {
  return between(v, w);
}

} // namespace liblevenshtein::distance
