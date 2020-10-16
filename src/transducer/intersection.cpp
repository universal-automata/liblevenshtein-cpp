#include <sstream>

#include "intersection.h"


namespace liblevenshtein {

    Intersection::Intersection(Intersection *parent, char label, DawgNode *node, State *state)
        : _parent(parent),
          _label(label),
          _node(node),
          _state(state)
    {}

    Intersection::Intersection(char label, DawgNode *node, State *state)
        : _parent(nullptr),
          _label(label),
          _node(node),
          _state(state)
    {}

    DawgNode *Intersection::node() const {
        return _node;
    }

    State *Intersection::state() const {
        return _state;
    }

    std::string Intersection::str() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &out, const Intersection &intersection) {
        if (intersection._parent != nullptr) {
            out << *(intersection._parent) << intersection._label;
        }
        return out;
    }

} // namespace liblevenshtein
