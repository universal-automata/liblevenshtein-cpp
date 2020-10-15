#include <sstream>

#include "intersection.h"


namespace liblevenshtein {

    Intersection::Intersection(Intersection *parent, char label, DawgNode *node, State *state)
        : parent(parent),
          label(label),
          node(node),
          state(state)
    {}

    Intersection::Intersection(char label, DawgNode *node, State *state)
        : parent(nullptr),
          label(label),
          node(node),
          state(state)
    {}

    DawgNode *Intersection::get_node() const {
        return node;
    }

    State *Intersection::get_state() const {
        return state;
    }

    std::string Intersection::str() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &out, const Intersection &intersection) {
        if (intersection.parent != nullptr) {
            out << *(intersection.parent) << intersection.label;
        }
        return out;
    }

} // namespace liblevenshtein
