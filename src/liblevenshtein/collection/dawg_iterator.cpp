#include "liblevenshtein/collection/dawg_iterator.h"


namespace liblevenshtein {

DawgIterator::DawgIterator(DawgNode* root) {
  auto *prefix = new Prefix(root);
  _prefixes.push_back(prefix);
  _pending.push(prefix);
  advance();
}

DawgIterator::DawgIterator(std::size_t term_index)
  : _term_index(term_index)
{}

DawgIterator::~DawgIterator() {
  for (Prefix* prefix : _prefixes) {
    delete prefix;
  }
}

auto DawgIterator::operator++() -> DawgIterator & {
  advance();
  _term_index += 1;
  return *this;
}

auto DawgIterator::operator*() const -> std::string {
  return _next_value;
}

auto DawgIterator::operator==(const DawgIterator &other) const -> bool {
  return _term_index == other._term_index;
}

void DawgIterator::advance() {
  if (!_pending.empty()) {
    DawgNode* node;
    std::string value;
    Prefix* prefix;

    do {
      prefix = _pending.front();
      _pending.pop();

      node = prefix->node();
      node->for_each_edge([&] (char label, DawgNode* target) {
        auto *child = new Prefix(target, prefix, label);
        _prefixes.push_back(child);
        _pending.push(child);
      });
    }
    while (!node->is_final() && !_pending.empty());

    if (node->is_final()) {
      _next_value = prefix->str();
    }
  }
}

} // namespace liblevenshtein
