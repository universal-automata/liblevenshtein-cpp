#include <cstdio>
#include <sstream>

#include "prefix.h"


namespace liblevenshtein {

    Prefix::Prefix(DawgNode* node, Prefix *parent, char label)
        : node(node),
          parent(parent),
          label(label)
    {}

    Prefix::Prefix(DawgNode* root)
        : node(root),
          parent(nullptr),
          label('\0')
    {}

    Prefix::Prefix(const Prefix &prefix)
        : node(prefix.node),
          parent(prefix.parent),
          label(prefix.label)
    {}

    Prefix::Prefix(Prefix &&prefix) noexcept
        : node(prefix.node),
          parent(prefix.parent),
          label(prefix.label)
    {}

    DawgNode* Prefix::get_node() const {
        return node;
    }

    char Prefix::get_label() const {
        return label;
    }

    std::string Prefix::str() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &out, const Prefix &prefix) {
        if (prefix.parent != nullptr) {
            out << *(prefix.parent) << prefix.label;
        }
        return out;
    }
} // namespace liblevenshtein
