#ifndef __LIBLEVENSHTEIN__COLLECTION__PREFIX_H__
#define __LIBLEVENSHTEIN__COLLECTION__PREFIX_H__

#include <iostream>
#include <string>

#include "liblevenshtein/collection/dawg_node.h"


namespace liblevenshtein {

    class Prefix {
    public:
        Prefix(DawgNode* node, Prefix* parent, char label);
        Prefix(DawgNode* root);
        Prefix(const Prefix &prefix);
        Prefix(Prefix &&prefix) noexcept;

        DawgNode* node() const;
        char label() const;
        std::string str() const;

        friend std::ostream &operator<<(std::ostream &out, const Prefix &prefix);

    private:
        DawgNode* _node;
        Prefix* _parent;
        char _label;
    };

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__COLLECTION__PREFIX_H__
