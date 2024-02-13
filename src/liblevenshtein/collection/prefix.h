#ifndef LIBLEVENSHTEIN_COLLECTION_PREFIX_H
#define LIBLEVENSHTEIN_COLLECTION_PREFIX_H

#include <iostream>
#include <string>

#include "liblevenshtein/collection/dawg_node.h"


namespace liblevenshtein {

  class Prefix {
  public:
    Prefix(DawgNode* node, Prefix* parent, char label);
    Prefix(DawgNode* root);
    Prefix(const Prefix &prefix) = default;
    Prefix(Prefix &&prefix) noexcept;

    [[nodiscard]] auto node() const -> DawgNode *;
    [[nodiscard]] auto label() const -> char;
    [[nodiscard]] auto str() const -> std::string;

    friend auto operator<<(std::ostream &out, const Prefix &prefix)
        -> std::ostream &;

  private:
    DawgNode* _node;
    Prefix* _parent;
    char _label;
  };

} // namespace liblevenshtein


#endif // LIBLEVENSHTEIN_COLLECTION_PREFIX_H
