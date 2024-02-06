#ifndef __LIBLEVENSHTEIN__COLLECTION__DAWG_H__
#define __LIBLEVENSHTEIN__COLLECTION__DAWG_H__

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "liblevenshtein/collection/dawg_iterator.h"
#include "liblevenshtein/collection/dawg_node.h"

namespace liblevenshtein {

    class Dawg {
    public:
        Dawg(DawgNode* root, std::size_t size);
        Dawg();
        virtual ~Dawg();

        virtual bool add(const std::string& term) = 0;
        virtual bool remove(const std::string& term) = 0;

        bool contains(const std::string& term) const;

        DawgNode* root() const;
        std::size_t size() const;

        DawgIterator begin() const;
        DawgIterator end() const;

        friend class std::hash<Dawg>;
        friend std::ostream& operator<<(std::ostream& out, const Dawg& dawg);

      protected:
        DawgNode* _root;
        std::size_t _size;

        std::unordered_set<DawgNode *> all_nodes() const;
    };
} // namespace liblevenshtein


namespace std {

    template <>
    struct hash<liblevenshtein::Dawg> {
        size_t operator()(const liblevenshtein::Dawg &dawg) const;
    };
} // namespace std


#endif // __LIBLEVENSHTEIN__COLLECTION__DAWG_H__
