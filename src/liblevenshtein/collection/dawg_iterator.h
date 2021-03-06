#ifndef __LIBLEVENSHTEIN__COLLECTION__DAWG_ITERATOR_H__
#define __LIBLEVENSHTEIN__COLLECTION__DAWG_ITERATOR_H__

#include <queue>
#include <vector>

#include "liblevenshtein/collection/dawg_node.h"
#include "liblevenshtein/collection/prefix.h"

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
        std::vector<Prefix *> _prefixes;
        std::queue<Prefix *> _pending;
        std::string _next_value;
        std::size_t _term_index = 0;

        void advance();
    };
} // namespace DawgIterator


#endif // __LIBLEVENSHTEIN__COLLECTION__DAWG_ITERATOR_H__
