#include <algorithm>
#include <cstdio>
#include <iterator>
#include <string>
#include <vector>
#include <set>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "../../src/collection/sorted_dawg.h"


struct std_str_cmp {
    bool operator()(const std::string &lhs, const std::string &rhs) const {
        return lhs < rhs;
    }
};


RC_GTEST_PROP(SortedDawg, contains_all_terms, (std::set<std::string, std_str_cmp> terms)) {
    liblevenshtein::Dawg *dawg = liblevenshtein::sorted_dawg(terms.begin(), terms.end());
    RC_ASSERT(dawg != nullptr);
    RC_ASSERT(terms.size() == dawg->get_size());
    for (const std::string &term : terms) {
        RC_ASSERT(dawg->contains(term));
    }
    delete dawg;
}


RC_GTEST_PROP(SortedDawg, does_not_contain_missing_terms,
              (std::set<std::string, std_str_cmp> terms_to_add,
               std::set<std::string, std_str_cmp> terms_to_ignore)) {

    std::vector<std::string> terms;

    // Remove all terms from terms_to_add that are in terms_to_ignore
    std::set_difference(terms_to_add.begin(), terms_to_add.end(),
                        terms_to_ignore.begin(), terms_to_ignore.end(),
                        std::inserter(terms, terms.begin()));

    liblevenshtein::Dawg *dawg = liblevenshtein::sorted_dawg(terms.begin(), terms.end());
    RC_ASSERT(dawg != nullptr);

    if (terms_to_add.find("") == terms_to_add.end()) {
        RC_ASSERT(!dawg->contains(""));
    }

    for (const std::string& term : terms_to_ignore) {
        RC_ASSERT(!dawg->contains(term));
    }

    delete dawg;
}
