#include <cstdio>

#include "dawg_iterator.h"


namespace liblevenshtein {

    DawgIterator::DawgIterator(DawgNode* root) {
        Prefix* prefix = new Prefix(root);
        prefixes.push_back(prefix);
        pending.push(prefix);
        advance();
    }

    DawgIterator::DawgIterator(std::size_t term_index)
        : term_index(term_index)
    {}

    DawgIterator::~DawgIterator() {
        for (Prefix* prefix : prefixes) {
            delete prefix;
        }
    }

    DawgIterator& DawgIterator::operator++() {
        advance();
        term_index += 1;
        return *this;
    }

    std::string DawgIterator::operator*() const {
        return next_value;
    }

    bool DawgIterator::operator!=(const DawgIterator& other) const {
        return term_index < other.term_index;
    }

    void DawgIterator::advance() {
        if (!pending.empty()) {
            DawgNode* node;
            std::string value;
            Prefix* prefix;

            do {
                prefix = pending.front();
                pending.pop();

                node = prefix->get_node();
                node->for_each_edge([&] (char label, DawgNode* target) {
                    Prefix* child = new Prefix(target, prefix, label);
                    prefixes.push_back(child);
                    pending.push(child);
                });
            }
            while (!node->is_final() && !pending.empty());

            if (node->is_final()) {
                next_value = prefix->str();
            }
        }
    }
} // namespace liblevenshtein
