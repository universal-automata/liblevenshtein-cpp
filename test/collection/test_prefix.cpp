#include <sstream>
#include <string>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "../../src/collection/prefix.h"


RC_GTEST_PROP(Prefix, returns_original_string, (const std::string term)) {
    liblevenshtein::Prefix* prefix = new liblevenshtein::Prefix();

    for (int i = 0; i < term.length(); i += 1) {
        prefix = new liblevenshtein::Prefix(prefix, term[i]);
    }

    std::stringstream ss;
    ss << *prefix;
    RC_ASSERT(term == ss.str());

    delete prefix;
}
