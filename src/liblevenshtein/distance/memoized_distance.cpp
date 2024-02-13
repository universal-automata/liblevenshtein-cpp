#include <mutex>

#include "liblevenshtein/distance/memoized_distance.h"

using namespace std::literals;


namespace liblevenshtein {

auto MemoizedDistance::operator()(const std::string &v, const std::string &w)
    -> std::size_t {
  return between(v, w);
}

auto MemoizedDistance::get(const SymmetricPair &key, std::size_t &distance) -> bool {
  std::shared_lock reader(mutex);
  auto iter = memo.find(key);
  if (iter != memo.end()) {
    distance = iter->second;
    return true;
  }
  return false;
}

auto MemoizedDistance::set(const SymmetricPair &key,
                           const std::size_t &distance) -> std::size_t {
  std::unique_lock writer(mutex);
  memo[key] = distance;
  return distance;
}

auto MemoizedDistance::f(const std::string &u, std::size_t const t) -> std::string {
  if (t < u.length()) {
    return u.substr(1 + t);
  }
  return "";
}

} // namespace liblevenshtein
