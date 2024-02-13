#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "liblevenshtein/distance/standard_distance.h"


static liblevenshtein::StandardDistance d;

RC_GTEST_PROP(StandardDistance, satisfies_non_negativity,
              (const std::string &x, const std::string &y)) {
  RC_ASSERT(d(x, y) >= 0);
}

RC_GTEST_PROP(StandardDistance, satisfies_indiscernible_identity,
              (const std::string &x, const std::string &y)) {
  if (d(x, y) == 0) {
    RC_ASSERT(x == y);
  }
}

RC_GTEST_PROP(StandardDistance, satisfies_symmetry,
              (const std::string &x, const std::string &y)) {
  RC_ASSERT(d(x, y) == d(y, x));
}

RC_GTEST_PROP(StandardDistance, satisfies_triangle_inequality,
              (const std::string &x, const std::string &y,
               const std::string &z)) {
  RC_ASSERT(d(x, y) <= d(x, z) + d(z, y));
}

RC_GTEST_PROP(StandardDistance, satisfies_left_and_right_invariance,
              (const std::string &x, const std::string &y,
               const std::string &z)) {
  RC_ASSERT(d(z + x, z + y) == d(x, y));
  RC_ASSERT(d(x + z, y + z) == d(x, y));
}
