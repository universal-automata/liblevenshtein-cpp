#include "liblevenshtein/test/utils/position_utils.h"
#include "liblevenshtein/test/types.h"

namespace liblevenshtein::test {

auto to_positions(const std::vector<Triple> &triples) -> std::vector<Position *> {
  std::vector<Position *> positions;
  positions.reserve(triples.size());
  for (const Triple &triple : triples) {
    positions.push_back(new Position(std::get<0>(triple), std::get<1>(triple),
                                     std::get<2>(triple)));
  }
  return positions;
}

} // namespace liblevenshtein
