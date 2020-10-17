#ifndef __LIBLEVENSHTEIN__COLLECTION__TRANSITION_H__
#define __LIBLEVENSHTEIN__COLLECTION__TRANSITION_H__

#include "liblevenshtein/collection/dawg_node.h"


namespace liblevenshtein {

    class Transition {
    public:
        Transition(char label, DawgNode* source, DawgNode* target);
        Transition(const Transition& transition);
        Transition(Transition&& transition) noexcept;

        char label() const;
        DawgNode* source() const;
        DawgNode* target() const;

        bool operator==(const Transition &other) const;
        bool operator!=(const Transition &other) const;

      private:
        char _label;
        DawgNode* _source;
        DawgNode* _target;
    };
} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__COLLECTION__TRANSITION_H__
