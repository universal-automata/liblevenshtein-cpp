#ifndef __LIBLEVENSHTEIN__TRANSDUCER__INTERSECTION_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__INTERSECTION_H__

#include <iostream>
#include <string>

#include "../collection/dawg_node.h"
#include "algorithm.h"
#include "state.h"


namespace liblevenshtein {

    template <Algorithm Type, class Node>
    class Intersection;

    template <Algorithm Type, class Node>
    std::ostream &operator<<(std::ostream &out, const Intersection<Type, Node> &intersection);

    template <Algorithm Type, class Node>
    class Intersection {
    public:
        Intersection(Intersection<Type, Node> *parent,
                     char label, Node *node, State<Type> *state);

        Intersection(char label, Node *node, State<Type> *state);

        std::string str() const;

        friend std::ostream &operator << <Type, Node>(
            std::ostream &out,
            const Intersection<Type, Node> &intersection);

      private:
        Intersection<Type, Node> *parent;
        char label;
        Node *node;
        State<Type> *state;
    };

    template class Intersection<Algorithm::STANDARD, DawgNode>;
    template class Intersection<Algorithm::TRANSPOSITION, DawgNode>;
    template class Intersection<Algorithm::MERGE_AND_SPLIT, DawgNode>;

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__INTERSECTION_H__
