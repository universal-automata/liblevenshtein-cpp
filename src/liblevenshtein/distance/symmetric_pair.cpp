#include <cstdint>

#include "MurmurHash2.h"

#include "liblevenshtein/distance/symmetric_pair.h"

namespace liblevenshtein::distance {

SymmetricPair::SymmetricPair(const std::string &first, const std::string &second) {
  if (first.compare(second) < 0) {
    this->first = first;
    this->second = second;
  } else {
    this->first = second;
    this->second = first;
  }
}

auto SymmetricPair::operator==(const SymmetricPair &other) const -> bool {
  return (first == other.first) && (second == other.second);
}

auto SymmetricPair::operator!=(const SymmetricPair &other) const -> bool {
  return !(*this == other);
}

auto operator<<(std::ostream &out, const SymmetricPair &pair)
    -> std::ostream & {
  out << "SymmetricPair{first=\"" << pair.first << "\", second=\"" << pair.second << "\"}";
  return out;
}

} // namespace liblevenshtein::distance

auto std::hash<liblevenshtein::distance::SymmetricPair>::operator()(
    const liblevenshtein::distance::SymmetricPair &pair) const -> std::size_t {
  std::uint64_t hash_code = 0xDEADBEEF;
  hash_code = MurmurHash64A(pair.first.c_str(), (int) pair.first.length(), hash_code);
  return MurmurHash64A(pair.second.c_str(), (int) pair.second.length(), hash_code);
}
