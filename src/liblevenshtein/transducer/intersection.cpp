#include <sstream>

#include "liblevenshtein/transducer/intersection.h"
#include "liblevenshtein/transducer/position.h"

namespace liblevenshtein {

    Intersection::Intersection(char label, DawgNode *node, State *state, Intersection *parent)
        : _parent(parent),
          _label(label),
          _node(node),
          _state(state) {}

    Intersection::~Intersection() {
        Position *head = _state->head();
        if (head->term_index() > 0 || head->num_errors() > 0) {
            // don't delete the initial state, it'll be deleted by the transducer
            delete _state;
        }
    }

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
