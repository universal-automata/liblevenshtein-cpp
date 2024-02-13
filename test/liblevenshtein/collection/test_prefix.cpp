#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "liblevenshtein/collection/dawg_node.h"
#include "liblevenshtein/collection/prefix.h"

namespace ll = liblevenshtein;

RC_GTEST_PROP(Prefix, returns_original_string, (const std::string &term)) {
  std::vector<ll::DawgNode *> nodes;
  std::vector<ll::Prefix *> prefixes;

  auto *node = new ll::DawgNode(term.empty());
  nodes.push_back(node);

  auto *prefix = new ll::Prefix(node);
  prefixes.push_back(prefix);
  RC_ASSERT(*node == *(prefix->node()));

  for (int i = 0; i + 1 < term.length(); i += 1) {
    node = new ll::DawgNode();
    nodes.push_back(node);
    prefix = new ll::Prefix(node, prefix, term[i]);
    prefixes.push_back(prefix);
    RC_ASSERT(*node == *(prefix->node()));
    RC_ASSERT(term[i] == prefix->label());
  }

  if (!term.empty()) {
    node = new ll::DawgNode(true);
    nodes.push_back(node);
    prefix = new ll::Prefix(node, prefix, term[term.length() - 1]);
    prefixes.push_back(prefix);
    RC_ASSERT(*node == *(prefix->node()));
    RC_ASSERT(term[term.length() - 1] == prefix->label());
  }

  RC_ASSERT(term == prefix->str());

  for (ll::Prefix *prefix : prefixes) {
    delete prefix;
  }

  for (ll::DawgNode *node : nodes) {
    delete node;
  }
}
