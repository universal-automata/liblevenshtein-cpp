#include "liblevenshtein/collection/transition.h"


namespace liblevenshtein {

Transition::Transition(char label, DawgNode* source, DawgNode* target)
  : _label(label),
    _source(source),
    _target(target)
{}

Transition::Transition(Transition &&transition) noexcept
  : _label(transition._label),
    _source(transition._source),
    _target(transition._target)
{}

auto Transition::label() const -> char {
  return _label;
}

auto Transition::source() const -> DawgNode * {
  return _source;
}

auto Transition::target() const -> DawgNode * {
  return _target;
}

auto Transition::operator==(const Transition &other) const -> bool {
  return _label == other._label
    && *_source == *(other._source)
    && *_target == *(other._target);
}

} // namespace liblevenshtein
