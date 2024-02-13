#include <sstream>

#include "liblevenshtein/transducer/intersection.h"

namespace liblevenshtein {

Intersection::Intersection(char label, DawgNode *node, State *state, Intersection *parent)
  : _parent(parent),
    _label(label),
    _node(node),
    _state(state) {}

Intersection::~Intersection() {
  delete _state;
}

auto Intersection::node() const -> DawgNode * {
  return _node;
}

auto Intersection::state() const -> State * {
  return _state;
}

auto Intersection::str() const -> std::string {
  std::stringstream ss;
  ss << *this;
  return ss.str();
}

auto operator<<(std::ostream &out, const Intersection &intersection)
    -> std::ostream & {
  if (intersection._parent != nullptr) {
    out << *(intersection._parent) << intersection._label;
  }
  return out;
}

} // namespace liblevenshtein
