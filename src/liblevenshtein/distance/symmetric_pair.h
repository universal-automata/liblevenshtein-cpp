#ifndef LIBLEVENSHTEIN_DISTANCE_SYMMETRIC_IMMUTABLE_PAIR_H
#define LIBLEVENSHTEIN_DISTANCE_SYMMETRIC_IMMUTABLE_PAIR_H

#include <iostream>
#include <string>


namespace liblevenshtein {

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
} // namespace liblevenshtein


namespace std {

  template <>
  struct hash<liblevenshtein::SymmetricPair> {
    auto operator()(const liblevenshtein::SymmetricPair &pair) const
        -> std::size_t;
  };
} // namespace std

#endif // __LIBLEVENSHTEIN__COLLECTION__SYMMETRIC_IMMUTABLE_PAIR_H__
