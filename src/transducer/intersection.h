#ifndef __LIBLEVENSHTEIN__TRANSDUCER__INTERSECTION_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__INTERSECTION_H__

#include <iostream>
#include <string>

#include "../collection/dawg_node.h"
#include "state.h"


namespace liblevenshtein {

    class Intersection {
    public:
        Intersection(Intersection *parent, char label, DawgNode *node, State *state);

        Intersection(char label, DawgNode *node, State *state);

        DawgNode *node() const;
        State *state() const;

        std::string str() const;

        friend std::ostream &operator<<(std::ostream &out, const Intersection &intersection);

    private:
        Intersection *_parent;
        char _label;
        DawgNode *_node;
        State *_state;
    };

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__INTERSECTION_H__
