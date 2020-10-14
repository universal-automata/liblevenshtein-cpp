#include <cstdio>

#include "../utils/MurmurHash2.h"
#include "dawg_node.h"


namespace liblevenshtein {

    DawgNode::DawgNode(std::map<char, DawgNode *> &edges)
        : edges(edges)
    {}

    bool DawgNode::is_final() const {
        return false;
    }

    std::vector<char> DawgNode::labels() const {
        std::vector<char> labels;
        for (const auto& [label, target] : edges) {
            labels.push_back(label);
        }
        return labels;
    }

    std::vector<DawgNode *> DawgNode::targets() const {
        std::vector<DawgNode *> targets;
        for (const auto& [label, target] : edges) {
            targets.push_back(target);
        }
        return targets;
    }

    void DawgNode::for_each_edge(std::function<void(char, DawgNode *)> fn) const {
        for (auto& [label, target] : edges) {
            fn(label, target);
        }
    }

    DawgNode* DawgNode::transition(char label) const {
        auto iter = edges.find(label);
        if (iter != edges.end()) {
            return iter->second;
        }
        return nullptr;
    }

    DawgNode* DawgNode::add_edge(char label, DawgNode* target) {
        DawgNode* existing = transition(label);
        if (existing != nullptr) {
            delete existing;
        }
        edges[label] = target;
        return this;
    }

    void DawgNode::clear() {
        edges.clear();
    }

    bool DawgNode::operator==(const DawgNode &other) const {
        if (is_final() != other.is_final()) {
            return false;
        }

        if (edges.size() != other.edges.size()) {
            return false;
        }

        for (auto const& [label, expected_target] : edges) {
            DawgNode* actual_target = other.transition(label);
            if (actual_target == nullptr || *expected_target != *actual_target) {
                return false;
            }
        }

        return true;
    }

    bool DawgNode::operator!=(const DawgNode &other) const {
        return !(*this == other);
    }

    std::ostream &operator<<(std::ostream &out, const DawgNode &node) {
        out << "DawgNode{is_final=" << (node.is_final() ? "true" : "false") << ", edges={";
        auto iter = node.edges.begin();
        if (iter != node.edges.end()) {
            out << "'" << iter->first << "':" << *(iter->second);
            while ((++iter) != node.edges.end()) {
                out << ", '" << iter->first << "':" << *(iter->second);
            }
        }
        out << "}}";
        return out;
    }
} // namespace liblevenshtein


std::size_t std::hash<liblevenshtein::DawgNode>::operator()(const liblevenshtein::DawgNode &node) const {
    uint64_t hash_code = 0xDEADBEEF;
    uint64_t key[1];

    for (const auto& [label, target] : node.edges) {
        key[0] = label;
        hash_code = MurmurHash64A(key, 1, hash_code);

        key[0] = (*this)(*target);
        hash_code = MurmurHash64A(key, 1, hash_code);
    }

    key[0] = node.is_final();
    return MurmurHash64A(key, 1, hash_code);
}
