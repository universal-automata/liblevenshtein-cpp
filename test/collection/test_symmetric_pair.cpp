#include <string>

#include <gtest/gtest.h>

#include "../../src/collection/symmetric_pair.h"

using namespace std::literals;


TEST(SymmetricPair, is_symmetric) {
    std::string foo("foo");
    std::string bar("bar");

    liblevenshtein::SymmetricPair pair1(foo, bar);
    liblevenshtein::SymmetricPair pair2(bar, foo);

    EXPECT_EQ(pair1, pair2);
    EXPECT_EQ(pair2, pair1);

    std::hash<liblevenshtein::SymmetricPair> hash;
    EXPECT_EQ(hash(pair1), hash(pair2));
}

TEST(SymmetricPair, is_comparable) {
  std::string foo("foo");
  std::string bar("bar");
  std::string baz("baz");

  liblevenshtein::SymmetricPair pair1(foo, bar);
  liblevenshtein::SymmetricPair pair2(bar, foo);
  liblevenshtein::SymmetricPair pair3(foo, baz);

  EXPECT_EQ(pair1, pair2);
  EXPECT_EQ(pair2, pair1);

  EXPECT_NE(pair1, pair3);
  EXPECT_NE(pair3, pair1);

  EXPECT_NE(pair2, pair3);
  EXPECT_NE(pair3, pair2);

  std::hash<liblevenshtein::SymmetricPair> hash;
  EXPECT_EQ(hash(pair1), hash(pair2));
  EXPECT_NE(hash(pair1), hash(pair3));
  EXPECT_NE(hash(pair2), hash(pair3));
}
