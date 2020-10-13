#include "prefix.h"


namespace liblevenshtein {

    Prefix::Prefix(Prefix *parent, char label)
        : parent(parent),
          label(label)
    {}

    Prefix::Prefix()
        : parent(nullptr),
          label('\0')
    {}

    Prefix::~Prefix() {
        if (parent != nullptr) {
            delete parent;
        }
    }

    std::ostream &operator<<(std::ostream &out, const Prefix &prefix) {
        if (prefix.parent != nullptr) {
            out << *(prefix.parent) << prefix.label;
        }
        return out;
    }
} // namespace liblevenshtein
