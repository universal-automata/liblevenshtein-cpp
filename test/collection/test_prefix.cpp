#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "../../src/collection/dawg_node.h"
#include "../../src/collection/final_dawg_node.h"
#include "../../src/collection/prefix.h"

namespace ll = liblevenshtein;


RC_GTEST_PROP(Prefix, returns_original_string, (const std::string term)) {
    std::vector<ll::DawgNode *> nodes;
    std::vector<ll::Prefix *> prefixes;

    ll::DawgNode* node = term.empty()
        ? new ll::FinalDawgNode()
        : new ll::DawgNode();
    nodes.push_back(node);

    ll::Prefix* prefix = new ll::Prefix(node);
    prefixes.push_back(prefix);
    RC_ASSERT(*node == *(prefix->get_node()));

    for (int i = 0; i + 1 < term.length(); i += 1) {
        node = new ll::DawgNode();
        nodes.push_back(node);
        prefix = new ll::Prefix(node, prefix, term[i]);
        prefixes.push_back(prefix);
        RC_ASSERT(*node == *(prefix->get_node()));
        RC_ASSERT(term[i] == prefix->get_label());
    }

    if (!term.empty()) {
        node = new ll::FinalDawgNode();
        nodes.push_back(node);
        prefix = new ll::Prefix(node, prefix, term[term.length() - 1]);
        prefixes.push_back(prefix);
        RC_ASSERT(*node == *(prefix->get_node()));
        RC_ASSERT(term[term.length() - 1] == prefix->get_label());
    }

    RC_ASSERT(term == prefix->str());

    for (ll::Prefix* prefix : prefixes) {
        delete prefix;
    }

    for (ll::DawgNode* node : nodes) {
        delete node;
    }
}
