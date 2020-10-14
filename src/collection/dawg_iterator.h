#ifndef __LIBLEVENSHTEIN__COLLECTION__DAWG_ITERATOR_H__
#define __LIBLEVENSHTEIN__COLLECTION__DAWG_ITERATOR_H__

#include <queue>
#include <vector>

#include "dawg_node.h"
#include "prefix.h"


namespace liblevenshtein {

    class DawgIterator {
    public:
        DawgIterator(DawgNode* root);
        DawgIterator(std::size_t term_index);
        ~DawgIterator();

        DawgIterator& operator++();
        std::string operator*() const;
        bool operator!=(const DawgIterator& other) const;
    private:
        std::vector<Prefix *> prefixes;
        std::queue<Prefix *> pending;
        std::string next_value;
        std::size_t term_index = 0;

        void advance();
    };
} // namespace DawgIterator


#endif // __LIBLEVENSHTEIN__COLLECTION__DAWG_ITERATOR_H__
