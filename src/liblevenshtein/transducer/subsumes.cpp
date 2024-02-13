#include "liblevenshtein/transducer/subsumes.h"

namespace liblevenshtein {

template <>
auto subsumes<Algorithm::STANDARD>(Position *lhs, Position *rhs, std::size_t n)
    -> bool {
  std::size_t i = lhs->term_index();
  std::size_t e = lhs->num_errors();
  std::size_t j = rhs->term_index();
  std::size_t f = rhs->num_errors();
  return ((i < j) ? (j - i) : (i - j)) <= (f - e);
}

template <>
auto subsumes<Algorithm::TRANSPOSITION>(Position *lhs, Position *rhs,
                                        std::size_t n) -> bool {
  std::size_t i = lhs->term_index();
  std::size_t e = lhs->num_errors();
  bool s = lhs->is_special();

  std::size_t j = rhs->term_index();
  std::size_t f = rhs->num_errors();
  bool t = lhs->is_special();

  if (s) {
    if (t) {
      return (i == j);
    }

    return (f == n) && (i == j);
  }

  if (t) {
    return ((j < i) ? (i - j - 1) : (j - i + 1)) <= (f - e);
  }

  return ((i < j) ? (j - i) : (i - j)) <= (f - e);
}

template <>
auto subsumes<Algorithm::MERGE_AND_SPLIT>(Position *lhs, Position *rhs,
                                          std::size_t n) -> bool {
  std::size_t i = lhs->term_index();
  std::size_t e = lhs->num_errors();
  bool s = lhs->is_special();
  std::size_t j = rhs->term_index();
  std::size_t f = rhs->num_errors();
  bool t = lhs->is_special();

  if (s && !t) {
    return false;
  }

  return ((i < j) ? (j - i) : (i - j)) <= (f - e);
}

} // namespace liblevenshtein
