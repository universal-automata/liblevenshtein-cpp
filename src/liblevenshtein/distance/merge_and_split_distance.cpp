#include "liblevenshtein/distance/merge_and_split_distance.h"
#include "liblevenshtein/distance/symmetric_pair.h"

namespace liblevenshtein {

auto MergeAndSplitDistance::between(std::string v, std::string w)
    -> std::size_t {
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

  char a = v[0];
  std::string x = v.substr(1);
  char b = w[0];
  std::string y = w.substr(1);

  // Discard identical characters
  while (a == b && !(x.empty() || y.empty())) {
    a = x[0];
    v = x;
    x = v.substr(1);
    b = y[0];
    w = y;
    y = w.substr(1);
  }

  // x.empty() || y.empty()
  if (a == b) {
    if (x.empty()) {
      return set(key, y.length());
    }
    return set(key, x.length());
  }

  distance = between(x, w);
  if (0 == distance) {
    return set(key, 1);
  }

  std::size_t min_distance = distance;

  distance = between(v, y);
  if (0 == distance) {
    return set(key, 1);
  }

  if (distance < min_distance) {
    min_distance = distance;
  }

  distance = between(x, y);
  if (0 == distance) {
    return set(key, 1);
  }

  if (distance < min_distance) {
    min_distance = distance;
  }

  if (w.length() > 1) {
    distance = between(x, f(w, 1));

    if (0 == distance) {
      return set(key, 1);
    }

    if (distance < min_distance) {
      min_distance = distance;
    }
  }

  if (v.length() > 1) {
    distance = between(f(v, 1), y);

    if (0 == distance) {
      return set(key, 1);
    }

    if (distance < min_distance) {
      min_distance = distance;
    }
  }

  return set(key, 1 + min_distance);
}

} // namespace liblevenshtein
