#ifndef __LIBLEVENSHTEIN__COLLECTION__PREFIX_H__
#define __LIBLEVENSHTEIN__COLLECTION__PREFIX_H__

#include <iostream>

#include "dawg_node.h"


namespace liblevenshtein {

    class Prefix {
    public:
        Prefix(Prefix* parent, char label);
        Prefix();
        ~Prefix();

        friend std::ostream &operator<<(std::ostream &out, const Prefix &prefix);
      private:
        Prefix* parent;
        char label;
    };

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__COLLECTION__PREFIX_H__
