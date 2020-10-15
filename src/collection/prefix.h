#ifndef __LIBLEVENSHTEIN__COLLECTION__PREFIX_H__
#define __LIBLEVENSHTEIN__COLLECTION__PREFIX_H__

#include <iostream>
#include <string>

#include "dawg_node.h"


namespace liblevenshtein {

    class Prefix {
    public:
        Prefix(DawgNode* node, Prefix* parent, char label);
        Prefix(DawgNode* root);
        Prefix(const Prefix &prefix);
        Prefix(Prefix &&prefix) noexcept;

        DawgNode* get_node() const;
        char get_label() const;
        std::string str() const;

        friend std::ostream &operator<<(std::ostream &out, const Prefix &prefix);
      private:
        DawgNode* node;
        Prefix* parent;
        char label;
    };

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__COLLECTION__PREFIX_H__