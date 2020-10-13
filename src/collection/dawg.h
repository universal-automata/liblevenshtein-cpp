#ifndef __LIBLEVENSHTEIN__COLLECTION__DAWG_H__
#define __LIBLEVENSHTEIN__COLLECTION__DAWG_H__

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "dawg_node.h"


namespace liblevenshtein {

    class Dawg {
    public:
        Dawg(DawgNode* root, int size);
        Dawg();
        virtual ~Dawg();

        virtual bool add(const std::string& term) = 0;
        virtual bool remove(const std::string& term) = 0;

        bool contains(const std::string& term) const;

        DawgNode* get_root() const;
        int get_size() const;

        friend class std::hash<Dawg>;
        friend std::ostream& operator<<(std::ostream& out, const Dawg& dawg);

      protected:
        DawgNode* root;
        int size;

        std::unordered_set<DawgNode *> all_nodes() const;
    };
} // namespace liblevenshtein


namespace std {

    template <>
    struct hash<liblevenshtein::Dawg> : unary_function<liblevenshtein::Dawg, size_t> {
        size_t operator()(const liblevenshtein::Dawg &dawg) const;
    };
} // namespace std


#endif // __LIBLEVENSHTEIN__COLLECTION__DAWG_H__
