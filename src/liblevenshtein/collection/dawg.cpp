#include <array>
#include <queue>

#include "MurmurHash2.h"

#include "liblevenshtein/collection/dawg.h"


namespace liblevenshtein {

Dawg::Dawg(DawgNode* root, std::size_t size)
  : _root(root),
    _size(size)
{}

Dawg::Dawg()
  : _root(new DawgNode()),
    _size(0)
{}

Dawg::~Dawg() {
  for (DawgNode* node : all_nodes()) {
    delete node;
  }
}

auto Dawg::all_nodes() const -> std::unordered_set<DawgNode *> {
  std::unordered_set<DawgNode *> nodes;
  std::queue<DawgNode *> pending;
  pending.push(_root);
  while (!pending.empty()) {
    DawgNode *node = pending.front();
    pending.pop();
    nodes.insert(node);
    node->for_each_edge([&](char label, DawgNode *target) {
      pending.push(target);
    });
  }
  return nodes;
}

auto Dawg::contains(const std::string &term) const -> bool {
  DawgNode* node = _root;
  for (int i = 0; i < term.length() && node != nullptr; i += 1) {
    node = node->transition(term[i]);
  }
  return node != nullptr && node->is_final();
}

auto Dawg::root() const -> DawgNode * {
  return _root;
}

auto Dawg::size() const -> std::size_t {
  return _size;
}

auto Dawg::begin() const -> DawgIterator {
  return {_root};
}

auto Dawg::end() const -> DawgIterator {
  return {_size};
}

auto operator<<(std::ostream &out, const Dawg &dawg) -> std::ostream & {
  out << "Dawg{size=" << dawg._size << ", root=" << dawg._root << "}";
  return out;
}

auto Dawg::operator==(const Dawg &other) const -> bool {
  return size() == other.size() && *root() == *other.root();
}

auto Dawg::operator!=(const Dawg &other) const -> bool {
  return !(*this == other);
}

} // namespace liblevenshtein


static std::hash<liblevenshtein::DawgNode> node_hash_code;

auto std::hash<liblevenshtein::Dawg>::operator()(
    const liblevenshtein::Dawg &dawg) const -> std::size_t {

  uint64_t hash_code = 0xDEADBEEF;

  std::array<uint64_t, 1> key = {dawg._size};
  hash_code = MurmurHash64A(key.data(), 1, hash_code);

  key[0] = node_hash_code(*(dawg._root));
  return MurmurHash64A(key.data(), 1, hash_code);
}
