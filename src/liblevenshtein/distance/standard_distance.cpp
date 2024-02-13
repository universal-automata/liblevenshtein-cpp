#include "liblevenshtein/distance/standard_distance.h"
#include "liblevenshtein/distance/symmetric_pair.h"

namespace liblevenshtein {

auto StandardDistance::between(std::string v, std::string w) -> std::size_t {
  const SymmetricPair key(v, w);

  std::size_t distance;
  if (get(key, distance)) {
    return distance;
  }

  if (v.empty()) {
    return set(key, w.length());
  }

  if (w.empty()) {
    return set(key, v.length());
  }

  char a = v[0]; std::string s = v.substr(1);
  char b = w[0]; std::string t = w.substr(1);

  // Discard identical characters
  while (a == b && !(s.empty() || t.empty())) {
    a = s[0]; v = s; s = v.substr(1);
    b = t[0]; w = t; t = w.substr(1);
  }

  // s.length() = 0 || t.length() == 0
  if (a == b) {
    if (s.empty()) {
      return set(key, t.length());
    }
    return set(key, s.length());
  }

  distance = between(s, w);
  if (0 == distance) {
    return set(key, 1);
  }

  std::size_t min_distance = distance;

  distance = between(v, t);
  if (0 == distance) {
    return set(key, 1);
  }

  if (distance < min_distance) {
    min_distance = distance;
  }

  distance = between(s, t);
  if (0 == distance) {
    return set(key, 1);
  }

  if (distance < min_distance) {
    min_distance = distance;
  }

  return set(key, 1 + min_distance);
}

} // namespace liblevenshtein
