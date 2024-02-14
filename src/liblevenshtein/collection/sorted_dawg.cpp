#include <algorithm>
#include <list>
#include <set>
#include <vector>

#include "liblevenshtein/collection/sorted_dawg.h"


namespace liblevenshtein {

SortedDawg::~SortedDawg() {
  clean_up();
}

auto SortedDawg::add(const std::string &term) -> bool {
  if (term < _prev_term) {
    return false;
  }

  if (term.empty()) {
    _root->is_final(true);
    _prev_term = term;
    _size += 1;
    return true;
  }

  std::size_t upper_bound = std::min(term.length(), _prev_term.length());

  // Find the length of the longest common prefix between term and prev_term
  std::size_t i = 0;
  while (i < upper_bound && term[i] == _prev_term[i]) {
    i += 1;
  }

  // Check the unchecked nodes for redundancy from the last one down to
  // the common prefix size. Then, truncate the list at that point.
  minimize(i);

  // Add the suffix starting from the correct node min-way through the graph
  DawgNode *source = unchecked_transitions->empty()
    ? _root
    : unchecked_transitions->top().target();

  for (std::size_t k = term.length(); i < k; i += 1) {
    auto *target = new DawgNode();
    floating_nodes->insert(target);
    unchecked_transitions->emplace(term[i], source, target);
    source = target;
  }

  source->is_final(true);
  _prev_term = term;
  _size += 1;
  return true;
}

void SortedDawg::finish() {
  minimize(0);
}

auto SortedDawg::minimized_node(DawgNode *key) const -> DawgNode * {
  auto iter = minimized_nodes->find(*key);
  if (iter != minimized_nodes->end()) {
    return iter->second;
  }
  return nullptr;
}

void SortedDawg::minimize(std::size_t lower_bound) {
  // proceed from the leaf up to a certain point
  for (std::size_t j = unchecked_transitions->size(); j > lower_bound; j -= 1) {
    Transition transition = unchecked_transitions->top();
    unchecked_transitions->pop();
    char label = transition.label();
    DawgNode* source = transition.source();
    DawgNode* target = transition.target();
    DawgNode* existing = minimized_node(target);
    if (existing != nullptr) {
      source->add_edge(label, existing);
    }
    else {
      source->add_edge(label, target);
      (*minimized_nodes)[*target] = target;
    }
  }
}

auto SortedDawg::remove(const std::string &term) -> bool {
  return false;
}

void SortedDawg::init() {
  unchecked_transitions = new std::stack<Transition>();
  minimized_nodes = new std::unordered_map<DawgNode, DawgNode *>();
  floating_nodes = new std::unordered_set<DawgNode *>();
}

void SortedDawg::clean_up() {
  if (unchecked_transitions != nullptr) {
    delete unchecked_transitions;
    unchecked_transitions = nullptr;
  }

  if (minimized_nodes != nullptr) {
    delete minimized_nodes;
    minimized_nodes = nullptr;
  }

  if (floating_nodes != nullptr) {
    for (DawgNode *node : all_nodes()) {
      floating_nodes->erase(node);
    }

    for (DawgNode *node : *floating_nodes) {
      delete node;
    }

    delete floating_nodes;
    floating_nodes = nullptr;
  }
}

template <class IterType>
auto sorted_dawg(IterType iter, IterType end) -> SortedDawg * {
  auto *dawg = new SortedDawg();
  dawg->init();

  while (iter != end) {
    const std::string &term = *iter;
    if (!dawg->add(term)) {
      delete dawg;
      return nullptr;
    }
    ++iter;
  }

  dawg->finish();
  dawg->clean_up();
  return dawg;
}

template
auto sorted_dawg(std::list<std::string>::iterator iter,
                 std::list<std::string>::iterator end) -> SortedDawg *;

template
auto sorted_dawg(std::vector<std::string>::iterator iter,
                 std::vector<std::string>::iterator end) -> SortedDawg *;

template
auto sorted_dawg(std::set<std::string>::iterator iter,
                 std::set<std::string>::iterator end) -> SortedDawg *;

} // namespace liblevenshtein
