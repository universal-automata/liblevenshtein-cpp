#include <queue>
#include <set>

#include "../utils/MurmurHash2.h"
#include "dawg.h"


namespace liblevenshtein {

    Dawg::Dawg(DawgNode* root, std::size_t size)
        : _root(root),
          _size(size)
    {}

    Dawg::Dawg()
        : _root(new DawgNode()),
          _size(0)
    {}

    Dawg::~Dawg() {
        for (DawgNode* node : all_nodes()) {
            delete node;
        }
    }

    std::unordered_set<DawgNode *> Dawg::all_nodes() const {
        std::unordered_set<DawgNode *> nodes;
        std::queue<DawgNode *> pending;
        pending.push(_root);
        while (!pending.empty()) {
            DawgNode *node = pending.front();
            pending.pop();
            nodes.insert(node);
            node->for_each_edge([&](char label, DawgNode *target) {
                pending.push(target);
            });
        }
        return nodes;
    }

    bool Dawg::contains(const std::string& term) const {
        DawgNode* node = _root;
        for (int i = 0; i < term.length() && node != nullptr; i += 1) {
            node = node->transition(term[i]);
        }
        return node != nullptr && node->is_final();
    }

    DawgNode* Dawg::root() const {
        return _root;
    }

    std::size_t Dawg::size() const {
        return _size;
    }

    DawgIterator Dawg::begin() const {
        return DawgIterator(_root);
    }

    DawgIterator Dawg::end() const {
        return DawgIterator(_size);
    }

    std::ostream& operator<<(std::ostream& out, const Dawg& dawg) {
        out << "Dawg{size=" << dawg._size << ", root=" << dawg._root << "}";
        return out;
    }
} // namespace liblevenshtein


static std::hash<liblevenshtein::DawgNode> node_hash_code;


std::size_t std::hash<liblevenshtein::Dawg>::operator()(const liblevenshtein::Dawg &dawg) const {
    uint64_t hash_code = 0xDEADBEEF;
    uint64_t key[1];

    key[0] = dawg._size;
    hash_code = MurmurHash64A(key, 1, hash_code);

    key[0] = node_hash_code(*(dawg._root));
    return MurmurHash64A(key, 1, hash_code);
}
