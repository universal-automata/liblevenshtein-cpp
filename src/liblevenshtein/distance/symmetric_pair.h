#ifndef LIBLEVENSHTEIN_DISTANCE_SYMMETRIC_IMMUTABLE_PAIR_H
#define LIBLEVENSHTEIN_DISTANCE_SYMMETRIC_IMMUTABLE_PAIR_H

#include <iostream>
#include <string>

namespace liblevenshtein::distance {

class SymmetricPair {
public:
  SymmetricPair(const std::string &first, const std::string &second);
  auto operator==(const SymmetricPair &other) const -> bool;
  auto operator!=(const SymmetricPair &other) const -> bool;

  friend class std::hash<SymmetricPair>;
  friend auto operator<<(std::ostream &out, const SymmetricPair &pair)
      -> std::ostream &;

private:
  std::string first;
  std::string second;
};

} // namespace liblevenshtein::distance

namespace std {

  template <>
  struct hash<liblevenshtein::distance::SymmetricPair> {
    auto operator()(const liblevenshtein::distance::SymmetricPair &pair) const
      -> std::size_t;
  };
} // namespace std

#endif // __LIBLEVENSHTEIN__COLLECTION__SYMMETRIC_IMMUTABLE_PAIR_H__
