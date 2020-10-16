#ifndef __LIBLEVENSHTEIN__COLLECTION__DAWG_NODE_H__
#define __LIBLEVENSHTEIN__COLLECTION__DAWG_NODE_H__

#include <functional>
#include <iostream>
#include <map>
#include <vector>


namespace liblevenshtein {

    class DawgNode {
    public:
        DawgNode(bool is_final = false);
        DawgNode(std::map<char, DawgNode *>& edges, bool is_final=false);

        void is_final(bool is_final);
        bool is_final() const;

        void for_each_edge(std::function<void(char, DawgNode *)> fn) const;

        DawgNode* transition(char label) const;
        DawgNode* add_edge(char label, DawgNode* target);

        bool operator==(const DawgNode &other) const;
        bool operator!=(const DawgNode &other) const;

    private:
        std::map<char, DawgNode *> _edges;
        bool _is_final = false;
    };
}

namespace std {

    template <>
    struct hash<liblevenshtein::DawgNode> : unary_function<liblevenshtein::DawgNode, size_t> {
        size_t operator()(const liblevenshtein::DawgNode &node) const;
    };
} // namespace std

#endif // __LIBLEVENSHTEIN__COLLECTION__DAWG_NODE_H__
