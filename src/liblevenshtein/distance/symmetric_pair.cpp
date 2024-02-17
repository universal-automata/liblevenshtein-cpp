#include <cstdint>

#include "MurmurHash2.h"

#include "liblevenshtein/distance/symmetric_pair.h"

namespace liblevenshtein::distance {

SymmetricPair::SymmetricPair(const std::string &u, const std::string &v) {
  if (u.compare(v) < 0) {
    this->first = u;
    this->second = v;
  } else {
    this->first = v;
    this->second = u;
  }
}

auto SymmetricPair::operator==(const SymmetricPair &other) const -> bool {
  return (first == other.first) && (second == other.second);
}

auto operator<<(std::ostream &out, const SymmetricPair &pair)
    -> std::ostream & {
  out << "SymmetricPair{first=\"" << pair.first << "\", second=\""
      << pair.second << "\"}";
  return out;
}

} // namespace liblevenshtein::distance

namespace std {

namespace lld = liblevenshtein::distance;

auto hash<lld::SymmetricPair>::operator()(const lld::SymmetricPair &pair) const
    -> size_t {
  uint64_t hash_code = 0xDEADBEEF;
  hash_code =
      MurmurHash64A(pair.first.c_str(), (int)pair.first.length(), hash_code);
  return MurmurHash64A(pair.second.c_str(), (int)pair.second.length(),
                       hash_code);
}

} // namespace std
