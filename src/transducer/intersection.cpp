#include <sstream>

#include "intersection.h"


namespace liblevenshtein {

    Intersection::Intersection(char label, DawgNode *node, State *state, Intersection *parent)
        : _parent(parent),
          _label(label),
          _node(node),
          _state(state) {
        if (parent != nullptr) {
            parent->inc_refs();
        }
    }

    Intersection::~Intersection() {
        if (_parent != nullptr) {
            _parent->dec_refs();
        }
    }

    DawgNode *Intersection::node() const {
        return _node;
    }

    State *Intersection::state() const {
        return _state;
    }

    void Intersection::inc_refs() {
        _num_refs += 1;
    }

    void Intersection::dec_refs() {
        _num_refs -= 1;
        if (_num_refs == 0) {
            delete this;
        }
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
