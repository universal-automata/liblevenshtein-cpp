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

        DawgNode *get_node() const;
        State *get_state() const;

        std::string str() const;

        friend std::ostream &operator<<(std::ostream &out, const Intersection &intersection);

      private:
        Intersection *parent;
        char label;
        DawgNode *node;
        State *state;
    };

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__INTERSECTION_H__
