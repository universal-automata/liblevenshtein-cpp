#include "../utils/MurmurHash2.h"
#include "dawg_node.h"

namespace liblevenshtein {

    DawgNode::DawgNode(std::map<char, DawgNode *> &edges, bool is_final)
        : _edges(edges),
          _is_final(is_final)
    {}

    DawgNode::DawgNode(bool is_final)
        : _is_final(is_final)
    {}

    void DawgNode::is_final(bool is_final) {
        _is_final = is_final;
    }

    bool DawgNode::is_final() const {
        return _is_final;
    }

    void DawgNode::for_each_edge(std::function<void(char, DawgNode *)> fn) const {
        for (auto& [label, target] : _edges) {
            fn(label, target);
        }
    }

    DawgNode* DawgNode::transition(char label) const {
        auto iter = _edges.find(label);
        if (iter != _edges.end()) {
            return iter->second;
        }
        return nullptr;
    }

    DawgNode* DawgNode::add_edge(char label, DawgNode* target) {
        DawgNode* existing = transition(label);
        if (existing != nullptr) {
            delete existing;
        }
        _edges[label] = target;
        return this;
    }

    bool DawgNode::operator==(const DawgNode &other) const {
        if (is_final() != other.is_final()) {
            return false;
        }

        if (_edges.size() != other._edges.size()) {
            return false;
        }

        for (auto const& [label, expected_target] : _edges) {
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
        auto iter = node._edges.begin();
        if (iter != node._edges.end()) {
            out << "'" << iter->first << "':" << *(iter->second);
            while ((++iter) != node._edges.end()) {
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

    for (const auto& [label, target] : node._edges) {
        key[0] = label;
        hash_code = MurmurHash64A(key, 1, hash_code);

        key[0] = (*this)(*target);
        hash_code = MurmurHash64A(key, 1, hash_code);
    }

    key[0] = node.is_final();
    return MurmurHash64A(key, 1, hash_code);
}
