#ifndef __LIBLEVENSHTEIN__COLLECTION__DAWG_NODE_H__
#define __LIBLEVENSHTEIN__COLLECTION__DAWG_NODE_H__

#include <functional>
#include <iostream>
#include <map>
#include <vector>


namespace liblevenshtein {

    class DawgNode {
    public:
        DawgNode() = default;
        DawgNode(std::map<char, DawgNode *>& edges);

        virtual bool is_final() const;
        std::vector<char> labels() const;
        std::vector<DawgNode *> targets() const;
        void for_each_edge(std::function<void(char, DawgNode *)> fn) const;
        DawgNode* transition(char label) const;
        DawgNode* add_edge(char label, DawgNode* target);
        void clear();

        bool operator==(const DawgNode &other) const;
        bool operator!=(const DawgNode &other) const;

        friend class std::hash<DawgNode>;
        friend std::ostream &operator<<(std::ostream &out, const DawgNode &node);

    private:
        std::map<char, DawgNode *> edges;
    };
}

namespace std {

    template <>
    struct hash<liblevenshtein::DawgNode> : unary_function<liblevenshtein::DawgNode, size_t> {
        size_t operator()(const liblevenshtein::DawgNode &node) const;
    };
} // namespace std

#endif // __LIBLEVENSHTEIN__COLLECTION__DAWG_NODE_H__
