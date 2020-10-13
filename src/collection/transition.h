#ifndef __LIBLEVENSHTEIN__COLLECTION__TRANSITION_H__
#define __LIBLEVENSHTEIN__COLLECTION__TRANSITION_H__

#include "dawg_node.h"


namespace liblevenshtein {

    class Transition {
    public:
        Transition(char label, DawgNode* source, DawgNode* target);
        Transition(const Transition& transition);
        Transition(Transition&& transition) noexcept;

        char get_label() const;
        DawgNode* get_source() const;
        DawgNode* get_target() const;

        bool operator==(const Transition &other) const;
        bool operator!=(const Transition &other) const;

      private:
        char label;
        DawgNode* source;
        DawgNode* target;
    };
} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__COLLECTION__TRANSITION_H__
