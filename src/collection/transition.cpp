#include <utility>

#include "transition.h"


namespace liblevenshtein {

    Transition::Transition(char label, DawgNode* source, DawgNode* target)
        : _label(label),
          _source(source),
          _target(target)
    {}

    Transition::Transition(const Transition &transition)
        : _label(transition._label),
          _source(transition._source),
          _target(transition._target)
    {}

    Transition::Transition(Transition &&transition) noexcept
        : _label(transition._label),
          _source(transition._source),
          _target(transition._target)
    {}

    char Transition::label() const {
        return _label;
    }

    DawgNode* Transition::source() const {
        return _source;
    }

    DawgNode* Transition::target() const {
        return _target;
    }

    bool Transition::operator==(const Transition &other) const {
        return _label == other._label
            && *_source == *(other._source)
            && *_target == *(other._target);
    }

    bool Transition::operator!=(const Transition &other) const {
        return !(*this == other);
    }

} // namespace liblevenshtein
