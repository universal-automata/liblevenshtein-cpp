#include <filesystem>
#include <string>
#include <set>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "liblevenshtein/collection/dawg.h"
#include "liblevenshtein/collection/sorted_dawg.h"
#include "liblevenshtein/serialization/serializer.h"

#include "liblevenshtein/test/utils/comparators.h"
#include "liblevenshtein/test/utils/file_utils.h"

namespace fs = std::filesystem;

namespace ll = liblevenshtein;
namespace llt = liblevenshtein::test;

RC_GTEST_PROP(ProtobufSerializer, restores_dawg,
              (const std::set<std::string, llt::std_str_cmp> &terms)) {
  ll::Dawg *expected = ll::sorted_dawg(terms.begin(), terms.end());
  RC_ASSERT(expected != nullptr);

  fs::path temp_path = llt::gen_temp_path("liblevenshtein-", ".pb");
  RC_ASSERT(ll::serialize_protobuf(expected, temp_path));

  ll::Dawg *actual = ll::deserialize_protobuf(temp_path);
  RC_ASSERT(actual != nullptr);
  RC_ASSERT(*expected == *actual);

  delete expected;
  delete actual;
}
