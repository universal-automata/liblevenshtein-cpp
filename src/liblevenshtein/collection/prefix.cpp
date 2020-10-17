#include <sstream>

#include "liblevenshtein/collection/prefix.h"


namespace liblevenshtein {

    Prefix::Prefix(DawgNode* node, Prefix *parent, char label)
        : _node(node),
          _parent(parent),
          _label(label)
    {}

    Prefix::Prefix(DawgNode* root)
        : _node(root),
          _parent(nullptr),
          _label('\0')
    {}

    Prefix::Prefix(const Prefix &prefix)
        : _node(prefix._node),
          _parent(prefix._parent),
          _label(prefix._label)
    {}

    Prefix::Prefix(Prefix &&prefix) noexcept
        : _node(prefix._node),
          _parent(prefix._parent),
          _label(prefix._label)
    {}

    DawgNode* Prefix::node() const {
        return _node;
    }

    char Prefix::label() const {
        return _label;
    }

    std::string Prefix::str() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &out, const Prefix &prefix) {
        if (prefix._parent != nullptr) {
            out << *(prefix._parent) << prefix._label;
        }
        return out;
    }
} // namespace liblevenshtein
