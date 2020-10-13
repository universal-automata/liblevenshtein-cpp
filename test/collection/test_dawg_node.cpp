#include <map>
#include <unordered_set>
#include <vector>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "../../src/collection/dawg_node.h"
#include "../../src/collection/final_dawg_node.h"

RC_GTEST_PROP(DawgNode, is_comparable, (const std::unordered_set<char> xs,
                                        const bool xs_is_final,
                                        const bool xs_has_final_transitions,
                                        const std::unordered_set<char> ys,
                                        const bool ys_is_final,
                                        const bool ys_has_final_transitions)) {

    liblevenshtein::DawgNode *xs_node = xs_is_final
        ? new liblevenshtein::FinalDawgNode()
        : new liblevenshtein::DawgNode();

    for (const char label : xs) {
        xs_node->add_edge(label, xs_has_final_transitions
            ? new liblevenshtein::FinalDawgNode()
            : new liblevenshtein::DawgNode());
    }

    liblevenshtein::DawgNode *ys_node = ys_is_final
        ? new liblevenshtein::FinalDawgNode()
        : new liblevenshtein::DawgNode();

    for (const char label : ys) {
        ys_node->add_edge(label, ys_has_final_transitions
            ? new liblevenshtein::FinalDawgNode()
            : new liblevenshtein::DawgNode());
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

RC_GTEST_PROP(DawgNode, has_equivalent_constructors, (const std::unordered_set<char> labels,
                                                      const bool is_final)) {
    liblevenshtein::DawgNode *lhs;
    liblevenshtein::DawgNode *rhs;

    std::map<char, liblevenshtein::DawgNode *> edges;
    for (const char label : labels) {
        edges[label] = new liblevenshtein::DawgNode();
    }

    if (is_final) {
        lhs = new liblevenshtein::FinalDawgNode();
        rhs = new liblevenshtein::FinalDawgNode(edges);
    }
    else {
        lhs = new liblevenshtein::DawgNode();
        rhs = new liblevenshtein::DawgNode(edges);
    }

    for (const char label : labels) {
        lhs->add_edge(label, new liblevenshtein::DawgNode());
    }

    RC_ASSERT(*lhs == *rhs);

    if (is_final) {
        RC_ASSERT(lhs->is_final());
        RC_ASSERT(rhs->is_final());
    }
    else {
        RC_ASSERT(!lhs->is_final());
        RC_ASSERT(!rhs->is_final());
    }

    delete lhs;
    delete rhs;
}

RC_GTEST_PROP(DawgNode, can_have_edges_added_and_cleared,
              (const std::unordered_set<char> labels,
               const bool is_final)) {

    liblevenshtein::DawgNode *node = is_final
        ? new liblevenshtein::FinalDawgNode()
        : new liblevenshtein::DawgNode();

    std::map<char, liblevenshtein::DawgNode *> edges;

    for (const char label : labels) {
        liblevenshtein::DawgNode *target = new liblevenshtein::DawgNode();
        edges[label] = target;
        node->add_edge(label, target);
    }

    std::vector<char> outgoing_labels = node->labels();
    RC_ASSERT(labels == std::unordered_set<char>(outgoing_labels.begin(), outgoing_labels.end()));

    for (const char label : labels) {
        liblevenshtein::DawgNode *target = node->transition(label);
        RC_ASSERT(target != nullptr);
        RC_ASSERT(target == edges[label]); // pointer comparison
    }

    node->clear();
    for (const char label : labels) {
        liblevenshtein::DawgNode *target = node->transition(label);
        RC_ASSERT(target == nullptr);
    }

    delete node;
}
