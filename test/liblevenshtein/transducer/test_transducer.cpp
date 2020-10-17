#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "liblevenshtein/collection/dawg.h"
#include "liblevenshtein/collection/sorted_dawg.h"
#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/transducer.h"
#include "liblevenshtein/distance/standard_distance.h"
#include "liblevenshtein/distance/transposition_distance.h"
#include "liblevenshtein/distance/merge_and_split_distance.h"

namespace ll = liblevenshtein;


static ll::StandardDistance standard_distance;
static ll::TranspositionDistance transposition_distance;
static ll::MergeAndSplitDistance merge_and_split_distance;

struct std_str_cmp {
    bool operator()(const std::string &lhs, const std::string &rhs) const {
        return lhs < rhs;
    }
};

RC_GTEST_PROP(StandardTransducer, contains_expected_terms,
              (std::set<std::string, std_str_cmp> dictionary_terms,
               std::set<std::string, std_str_cmp> query_terms,
               std::size_t max_distance)) {

    std::unordered_map<std::string, std::unordered_set<std::string>> expected_candidates;
    for (const std::string& query_term : query_terms) {
        std::unordered_set<std::string> spelling_candidates;
        for (const std::string& dictionary_term : dictionary_terms) {
            if (standard_distance(dictionary_term, query_term) <= max_distance) {
                spelling_candidates.insert(dictionary_term);
            }
        }
        expected_candidates[query_term] = spelling_candidates;
    }

    ll::Dawg *dawg = ll::sorted_dawg(dictionary_terms.begin(), dictionary_terms.end());
    ll::Transducer<ll::Algorithm::STANDARD, ll::Candidate> transduce(dawg->root());

    for (const std::string& query_term : query_terms) {
        std::unordered_set<std::string>& spelling_candidates = expected_candidates[query_term];
        for (const ll::Candidate& candidate : transduce(query_term, max_distance)) {
            const std::string& term = candidate.first;
            std::size_t distance = candidate.second;
            RC_ASSERT(spelling_candidates.find(term) != spelling_candidates.end());
            RC_ASSERT(distance == standard_distance(term, query_term));
            spelling_candidates.erase(term);
        }
        RC_ASSERT(spelling_candidates.empty());
    }
}
