#ifndef LIBLEVENSHTEIN_DISTANCE_DISTANCE_H
#define LIBLEVENSHTEIN_DISTANCE_DISTANCE_H

#include <string>

namespace liblevenshtein {

  class Distance {
  public:
    virtual auto between(std::string v, std::string w) -> std::size_t = 0;
    virtual auto operator()(const std::string &v, const std::string &w)
        -> std::size_t = 0;
  };

} // namespace liblevenshtein

#endif // LIBLEVENSHTEIN_DISTANCE_DISTANCE_H
