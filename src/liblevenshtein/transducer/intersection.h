#ifndef __LIBLEVENSHTEIN__TRANSDUCER__INTERSECTION_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__INTERSECTION_H__

#include <cstddef>
#include <iostream>
#include <string>

#include "liblevenshtein/collection/dawg_node.h"
#include "liblevenshtein/transducer/state.h"

namespace liblevenshtein {

    class Intersection {
    public:
        Intersection(char label, DawgNode *node, State *state, Intersection *parent = nullptr);
        ~Intersection();

        DawgNode *node() const;
        State *state() const;

        std::string str() const;
        friend std::ostream &operator<<(std::ostream &out, const Intersection &intersection);

    private:
        char _label;
        DawgNode *_node;
        State *_state;
        Intersection *_parent;
    };

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__INTERSECTION_H__
