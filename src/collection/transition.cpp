#include <utility>

#include "transition.h"


namespace liblevenshtein {

    Transition::Transition(char label, DawgNode* source, DawgNode* target)
        : label(label),
          source(source),
          target(target)
    {}

    Transition::Transition(const Transition &transition)
        : label(transition.label),
          source(transition.source),
          target(transition.target)
    {}

    Transition::Transition(Transition &&transition) noexcept
        : label(transition.label),
          source(transition.source),
          target(transition.target)
    {}

    char Transition::get_label() const {
        return label;
    }

    DawgNode* Transition::get_source() const {
        return source;
    }

    DawgNode* Transition::get_target() const {
        return target;
    }

    bool Transition::operator==(const Transition &other) const {
        return label == other.label
            && *source == *(other.source)
            && *target == *(other.target);
    }

    bool Transition::operator!=(const Transition &other) const {
        return !(*this == other);
    }

} // namespace liblevenshtein
