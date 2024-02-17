#ifndef LIBLEVENSHTEIN_DISTANCE_SYMMETRIC_IMMUTABLE_PAIR_H
#define LIBLEVENSHTEIN_DISTANCE_SYMMETRIC_IMMUTABLE_PAIR_H

#include <iostream>
#include <string>

namespace liblevenshtein::distance {

/**
 * Represents a pair of terms sorted, lexicographically, in ascending order.
 */
class SymmetricPair {
public:

  /**
   * Constructs a SymmetricPair of terms such that the first term is the lesser,
   * lexicographically, of the two.
   *
   * @param u The first term of the SymmetricPair.
   * @param v The second term of the SymmetricPair.
   */
  SymmetricPair(const std::string &u, const std::string &v);

  /**
   * Determines whether this SymmetricPair is equivalent to another.
   *
   * @param other The SymmetricPair to compare with this one.
   * @return Whether this SymmetricPair is equivalent to the other.
   */
  auto operator==(const SymmetricPair &other) const -> bool;

  /** The hasch function may access all the members of this class. */
  friend class std::hash<SymmetricPair>;

  /** The ostream operator may access all the members of this class. */
  friend auto operator<<(std::ostream &out, const SymmetricPair &pair)
      -> std::ostream &;

private:

  /** The lexicographically lesser term of the pair. */
  std::string first;

  /** The lexicographically greater term of the pair. */
  std::string second;
};

} // namespace liblevenshtein::distance

namespace std {

/**
 * Generates hash codes for SymmetricPair instances.
 */
template <>
struct hash<liblevenshtein::distance::SymmetricPair> {

  /**
   * Generates the hash code for a SymmetricPair.
   *
   * @param pair SymmetricPair whose hash code needs to be generated.
   * @return The hash code for the given SymmetricPair.
   */
  auto operator()(const liblevenshtein::distance::SymmetricPair &pair) const
    -> std::size_t;
};

} // namespace std

#endif // __LIBLEVENSHTEIN__COLLECTION__SYMMETRIC_IMMUTABLE_PAIR_H__
