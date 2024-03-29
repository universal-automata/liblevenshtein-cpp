#include <string>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "liblevenshtein/distance/symmetric_pair.h"

namespace lld = liblevenshtein::distance;

RC_GTEST_PROP(SymmetricPair, is_comparable,
              (const std::string &foo, const std::string &bar,
               const std::string &baz)) {
  std::hash<lld::SymmetricPair> hash;

  lld::SymmetricPair pair1(foo, bar);
  lld::SymmetricPair pair2(bar, foo);
  lld::SymmetricPair pair3(foo, baz);

  RC_ASSERT(pair1 == pair1);
  RC_ASSERT(pair2 == pair2);
  RC_ASSERT(pair3 == pair3);

  RC_ASSERT(pair1 == pair2);
  RC_ASSERT(pair2 == pair1);

  RC_ASSERT(hash(pair1) == hash(pair1));
  RC_ASSERT(hash(pair2) == hash(pair2));
  RC_ASSERT(hash(pair3) == hash(pair3));

  RC_ASSERT(hash(pair1) == hash(pair2));

  if (bar != baz) {
    RC_ASSERT(pair1 != pair3);
    RC_ASSERT(pair3 != pair1);

    RC_ASSERT(pair2 != pair3);
    RC_ASSERT(pair3 != pair2);

    RC_ASSERT(hash(pair1) != hash(pair3));
    RC_ASSERT(hash(pair2) != hash(pair3));
  }
}
