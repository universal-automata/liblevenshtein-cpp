#include <sstream>

#include "intersection.h"


namespace liblevenshtein {

    template <Algorithm Type, class Node>
    Intersection<Type, Node>::Intersection(Intersection<Type, Node> *parent,
                                           char label, Node *node, State<Type> *state)
        : parent(parent),
          label(label),
          node(node),
          state(state)
    {}

    template <Algorithm Type, class Node>
    Intersection<Type, Node>::Intersection(char label, Node *node, State<Type> *state)
        : parent(nullptr),
          label(label),
          node(node),
          state(state)
    {}

    template <Algorithm Type, class Node>
    std::string Intersection<Type, Node>::str() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    template <Algorithm Type, class Node>
    std::ostream &operator<<(std::ostream &out,
                             const Intersection<Type, Node> &intersection) {
        if (intersection.parent != nullptr) {
            out << *(intersection.parent);
        }
        out << intersection.label;
        return out;
    }

} // namespace liblevenshtein
