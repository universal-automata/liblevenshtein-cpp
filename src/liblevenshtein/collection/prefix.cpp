#include <sstream>

#include "liblevenshtein/collection/prefix.h"


namespace liblevenshtein {

Prefix::Prefix(DawgNode* node, Prefix *parent, char label)
  : _node(node),
    _parent(parent),
    _label(label)
{}

Prefix::Prefix(DawgNode* root)
  : _node(root),
    _parent(nullptr),
    _label('\0')
{}

Prefix::Prefix(Prefix &&prefix) noexcept
  : _node(prefix._node),
    _parent(prefix._parent),
    _label(prefix._label)
{}

auto Prefix::node() const -> DawgNode * {
  return _node;
}

auto Prefix::label() const -> char {
  return _label;
}

auto Prefix::str() const -> std::string {
  std::stringstream ss;
  ss << *this;
  return ss.str();
}

auto operator<<(std::ostream &out, const Prefix &prefix) -> std::ostream & {
  if (prefix._parent != nullptr) {
    out << *(prefix._parent) << prefix._label;
  }
  return out;
}

} // namespace liblevenshtein
