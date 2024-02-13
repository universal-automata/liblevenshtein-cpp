#include <map>
#include <unordered_set>
#include <vector>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "liblevenshtein/collection/dawg_node.h"

namespace ll = liblevenshtein;

RC_GTEST_PROP(DawgNode, is_comparable,
              (const std::unordered_set<char> &xs, const bool xs_is_final,
               const bool xs_has_final_transitions,
               const std::unordered_set<char> &ys, const bool ys_is_final,
               const bool ys_has_final_transitions)) {

  auto *xs_node = new ll::DawgNode(xs_is_final);

  for (const char label : xs) {
    xs_node->add_edge(label, new ll::DawgNode(xs_has_final_transitions));
  }

  auto *ys_node = new ll::DawgNode(ys_is_final);

  for (const char label : ys) {
    ys_node->add_edge(label, new ll::DawgNode(ys_has_final_transitions));
  }

  if (xs == ys && xs_is_final == ys_is_final &&
      (xs_has_final_transitions == ys_has_final_transitions || xs.empty())) {
    RC_ASSERT(*xs_node == *ys_node);
  } else {
    RC_ASSERT(*xs_node != *ys_node);
  }

  delete xs_node;
  delete ys_node;
}

RC_GTEST_PROP(DawgNode, has_equivalent_constructors,
              (const std::unordered_set<char> &labels, const bool is_final)) {
  ll::DawgNode *lhs;
  ll::DawgNode *rhs;

  std::map<char, ll::DawgNode *> edges;
  for (const char label : labels) {
    edges[label] = new ll::DawgNode();
  }

  if (is_final) {
    lhs = new ll::DawgNode(true);
    rhs = new ll::DawgNode(edges, true);
  } else {
    lhs = new ll::DawgNode();
    rhs = new ll::DawgNode(edges);
  }

  for (const char label : labels) {
    lhs->add_edge(label, new ll::DawgNode());
  }

  RC_ASSERT(*lhs == *rhs);

  if (is_final) {
    RC_ASSERT(lhs->is_final());
    RC_ASSERT(rhs->is_final());
  } else {
    RC_ASSERT(!lhs->is_final());
    RC_ASSERT(!rhs->is_final());
  }

  delete lhs;
  delete rhs;
}

RC_GTEST_PROP(DawgNode, can_have_edges_added,
              (const std::unordered_set<char> &labels, const bool is_final)) {

  auto *node = new ll::DawgNode(is_final);

  std::map<char, ll::DawgNode *> edges;

  for (const char label : labels) {
    auto *target = new ll::DawgNode();
    edges[label] = target;
    node->add_edge(label, target);
  }

  std::vector<char> outgoing_labels;
  node->for_each_edge([&](char label, ll::DawgNode *target) {
    outgoing_labels.push_back(label);
  });

  RC_ASSERT(labels == std::unordered_set<char>(outgoing_labels.begin(),
                                               outgoing_labels.end()));

  for (const char label : labels) {
    ll::DawgNode *target = node->transition(label);
    RC_ASSERT(target != nullptr);
    RC_ASSERT(target == edges[label]); // pointer comparison
  }

  delete node;
}
