#include <algorithm>
#include <cstdio>
#include <iterator>
#include <random>
#include <string>
#include <vector>
#include <set>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "../../src/collection/sorted_dawg.h"

namespace ll = liblevenshtein;


struct std_str_cmp {
    bool operator()(const std::string &lhs, const std::string &rhs) const {
        return lhs < rhs;
    }
};


bool is_sorted(std::vector<std::string>& terms) {
    std::string prev = terms[0];
    for (int i = 1; i < terms.size(); i += 1) {
        if (prev > terms[i]) {
            return false;
        }
        prev = terms[i];
    }
    return true;
}


RC_GTEST_PROP(SortedDawg, rejects_unsorted_terms, (std::set<std::string> terms, unsigned seed)) {
    RC_PRE(terms.size() > 1);
    std::vector terms_to_add(terms.begin(), terms.end());
    std::default_random_engine random_engine(seed);
    while (is_sorted(terms_to_add)) {
        std::shuffle(terms_to_add.begin(), terms_to_add.end(), random_engine);
    }
    ll::Dawg *dawg = ll::sorted_dawg(terms_to_add.begin(), terms_to_add.end());
    RC_ASSERT(dawg == nullptr);
}


RC_GTEST_PROP(SortedDawg, contains_expected_terms,
              (std::set<std::string, std_str_cmp> terms_to_add,
               std::set<std::string, std_str_cmp> terms_to_ignore)) {

    for (const std::string& term : terms_to_ignore) {
        terms_to_add.erase(term);
    }

    ll::Dawg *dawg = ll::sorted_dawg(terms_to_add.begin(), terms_to_add.end());
    RC_ASSERT(dawg != nullptr);

    if (terms_to_add.find("") == terms_to_add.end()) {
        RC_ASSERT(!dawg->contains(""));
    }

    for (const std::string& term : terms_to_add) {
        RC_ASSERT(dawg->contains(term));
    }

    for (const std::string& term : terms_to_ignore) {
        RC_ASSERT(!dawg->contains(term));
    }

    for (std::string term : *dawg) {
        RC_ASSERT(terms_to_add.find(term) != terms_to_add.end());
        terms_to_add.erase(term);
    }
    RC_ASSERT(terms_to_add.empty());

    delete dawg;
}
