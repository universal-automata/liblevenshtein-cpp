#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "liblevenshtein/collection/dawg.h"
#include "liblevenshtein/collection/sorted_dawg.h"
#include "liblevenshtein/distance/distance.h"
#include "liblevenshtein/distance/merge_and_split_distance.h"
#include "liblevenshtein/distance/standard_distance.h"
#include "liblevenshtein/distance/transposition_distance.h"
#include "liblevenshtein/transducer/algorithm.h"
#include "liblevenshtein/transducer/test_helpers.h"
#include "liblevenshtein/transducer/transducer.h"

namespace ll = liblevenshtein;

static ll::StandardDistance standard_distance;
static ll::TranspositionDistance transposition_distance;
static ll::MergeAndSplitDistance merge_and_split_distance;

template <ll::Algorithm Type>
void test_transducer(std::set<std::string, ll::std_str_cmp> dictionary_terms,
                     std::set<std::string, ll::std_str_cmp> query_terms,
                     std::size_t max_distance, ll::Distance &d) {

    std::unordered_map<std::string, std::unordered_set<std::string>> expected_candidates;
    for (const std::string &query_term : query_terms) {
        std::unordered_set<std::string> spelling_candidates;
        for (const std::string &dictionary_term : dictionary_terms) {
            std::size_t distance = d(dictionary_term, query_term);
            if (distance <= max_distance) {
                spelling_candidates.insert(dictionary_term);
            }
        }
        expected_candidates[query_term] = spelling_candidates;
    }

    ll::Dawg *dawg = ll::sorted_dawg(dictionary_terms.begin(), dictionary_terms.end());

    ll::Transducer<Type, ll::Candidate> transduce_candidates(dawg->root());
    for (const std::string &query_term : query_terms) {
        std::unordered_set<std::string> spelling_candidates(expected_candidates[query_term]);
        for (const ll::Candidate &candidate : transduce_candidates(query_term, max_distance)) {
            const std::string &term = candidate.first;
            const std::size_t distance = candidate.second;
            RC_ASSERT(spelling_candidates.find(term) != spelling_candidates.end());
            RC_ASSERT(distance == d(term, query_term));
            spelling_candidates.erase(term);
        }
        RC_ASSERT(spelling_candidates.empty());
    }

    ll::Transducer<Type, std::string> transduce_terms(dawg->root());
    for (const std::string &query_term : query_terms) {
        std::unordered_set<std::string> &spelling_candidates = expected_candidates[query_term];
        for (const std::string &term : transduce_terms(query_term, max_distance)) {
            RC_ASSERT(spelling_candidates.find(term) != spelling_candidates.end());
            spelling_candidates.erase(term);
        }
        RC_ASSERT(spelling_candidates.empty());
    }

    delete dawg;
}

RC_GTEST_PROP(StandardTransducer, contains_expected_terms,
              (std::set<std::string, ll::std_str_cmp> dictionary_terms,
               std::set<std::string, ll::std_str_cmp> query_terms,
               std::size_t max_distance)) {
    test_transducer<ll::Algorithm::STANDARD>(dictionary_terms, query_terms,
                                             max_distance, standard_distance);
}

RC_GTEST_PROP(TranspositionTransducer, contains_expected_terms,
              (std::set<std::string, ll::std_str_cmp> dictionary_terms,
               std::set<std::string, ll::std_str_cmp> query_terms,
               std::size_t max_distance)) {
  test_transducer<ll::Algorithm::TRANSPOSITION>(dictionary_terms, query_terms,
                                                max_distance, transposition_distance);
}

RC_GTEST_PROP(MergeAndSplitTransducer, contains_expected_terms,
              (std::set<std::string, ll::std_str_cmp> dictionary_terms,
               std::set<std::string, ll::std_str_cmp> query_terms,
               std::size_t max_distance)) {
  test_transducer<ll::Algorithm::MERGE_AND_SPLIT>(dictionary_terms, query_terms,
                                                  max_distance, merge_and_split_distance);
}
