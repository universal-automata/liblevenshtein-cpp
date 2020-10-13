#include <queue>
#include <set>

#include "../utils/MurmurHash2.h"
#include "dawg.h"


namespace liblevenshtein {

    Dawg::Dawg(DawgNode* root, int size)
        : root(root),
          size(size)
    {}

    Dawg::Dawg()
        : root(new DawgNode()),
          size(0)
    {}

    Dawg::~Dawg() {
        for (DawgNode* node : all_nodes()) {
            delete node;
        }
    }

    std::unordered_set<DawgNode *> Dawg::all_nodes() const {
        std::unordered_set<DawgNode *> nodes;
        std::queue<DawgNode *> pending;
        pending.push(root);
        while (!pending.empty()) {
            DawgNode *node = pending.front();
            pending.pop();
            nodes.insert(node);
            for (DawgNode *target : node->targets()) {
                pending.push(target);
            }
        }
        return nodes;
    }

    bool Dawg::contains(const std::string& term) const {
        DawgNode* node = root;
        for (int i = 0; i < term.length() && node != nullptr; i += 1) {
            node = node->transition(term[i]);
        }
        return node != nullptr && node->is_final();
    }

    DawgNode* Dawg::get_root() const {
        return root;
    }

    int Dawg::get_size() const {
        return size;
    }

    std::ostream& operator<<(std::ostream& out, const Dawg& dawg) {
        out << "Dawg{size=" << dawg.size << ", root=" << dawg.root << "}";
        return out;
    }
} // namespace liblevenshtein


static std::hash<liblevenshtein::DawgNode> node_hash_code;


std::size_t std::hash<liblevenshtein::Dawg>::operator()(const liblevenshtein::Dawg &dawg) const {
    uint64_t hash_code = 0xDEADBEEF;
    uint64_t key[1];

    key[0] = dawg.size;
    hash_code = MurmurHash64A(key, 1, hash_code);

    key[0] = node_hash_code(*(dawg.root));
    return MurmurHash64A(key, 1, hash_code);
}
