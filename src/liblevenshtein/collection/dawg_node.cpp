#include <array>
#include <iostream>

#include "MurmurHash2.h"

#include "liblevenshtein/collection/dawg_node.h"

namespace liblevenshtein {

DawgNode::DawgNode(std::map<char, DawgNode *> &edges, bool is_final)
  : _edges(edges),
    _is_final(is_final)
{}

DawgNode::DawgNode(bool is_final)
  : _is_final(is_final)
{}

void DawgNode::is_final(bool is_final) {
  _is_final = is_final;
}

auto DawgNode::is_final() const -> bool {
  return _is_final;
}

void DawgNode::for_each_edge(const std::function<void(char, DawgNode *)> &fn) const {
  for (const auto &[label, target] : _edges) {
    fn(label, target);
  }
}

auto DawgNode::transition(char label) const -> DawgNode * {
  auto iter = _edges.find(label);
  if (iter != _edges.end()) {
    return iter->second;
  }
  return nullptr;
}

auto DawgNode::add_edge(char label, DawgNode *target) -> DawgNode * {
  DawgNode* existing = transition(label);
  delete existing;
  _edges[label] = target;
  return this;
}

#if _MSC_VER && !__INTEL_COMPILER
#pragma warning(once : 5232)
#endif

auto DawgNode::operator==(const DawgNode &other) const -> bool {
  if (is_final() != other.is_final()) {
    return false;
  }

  if (_edges.size() != other._edges.size()) {
    return false;
  }

  // NOLINTNEXTLINE(readability-use-anyofallof)
  for (const auto &[label, expected_target] : _edges) {
    DawgNode *actual_target = other.transition(label);
    if (actual_target == nullptr || *expected_target != *actual_target) {
      return false;
    }
  }

  return true;
}

auto operator<<(std::ostream &out, const DawgNode &node) -> std::ostream & {
  out << "DawgNode{is_final=" << (node.is_final() ? "true" : "false") << ", edges={";
  int index = 0;
  node.for_each_edge([&](char label, DawgNode *target) {
    if (index > 0) {
      out << ", ";
    }
    out << "'" << label << "':DawgNode{...}";
    index += 1;
  });
  out << "}}";
  return out;
}

} // namespace liblevenshtein

auto std::hash<liblevenshtein::DawgNode>::operator()(
    const liblevenshtein::DawgNode &node) const -> std::size_t {

  uint64_t hash_code = 0xDEADBEEF;
  std::array<uint64_t, 1> key = {0};

  node.for_each_edge([&](char label, liblevenshtein::DawgNode *target) {
    key[0] = (unsigned char) label;
    hash_code = MurmurHash64A(key.data(), 1, hash_code);

    key[0] = (*this)(*target);
    hash_code = MurmurHash64A(key.data(), 1, hash_code);
  });

  key[0] = (uint64_t) node.is_final();
  return MurmurHash64A(key.data(), 1, hash_code);
}
