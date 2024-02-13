#ifndef LIBLEVENSHTEIN_COLLECTION_DAWG_H
#define LIBLEVENSHTEIN_COLLECTION_DAWG_H

#include <iostream>
#include <string>
#include <unordered_set>

#include "liblevenshtein/collection/dawg_iterator.h"
#include "liblevenshtein/collection/dawg_node.h"

namespace liblevenshtein {

  class Dawg {
  public:
    Dawg(DawgNode* root, std::size_t size);
    Dawg();
    virtual ~Dawg();

    virtual auto add(const std::string &term) -> bool = 0;
    virtual auto remove(const std::string &term) -> bool = 0;

    [[nodiscard]] auto contains(const std::string &term) const -> bool;

    [[nodiscard]] auto root() const -> DawgNode *;
    [[nodiscard]] auto size() const -> size_t;

    [[nodiscard]] auto begin() const -> DawgIterator;
    [[nodiscard]] auto end() const -> DawgIterator;

    auto operator==(const Dawg &other) const -> bool;
    auto operator!=(const Dawg &other) const -> bool;

    friend class std::hash<Dawg>;
    friend auto operator<<(std::ostream &out, const Dawg &dawg)
        -> std::ostream &;

  protected:
    DawgNode* _root;
    std::size_t _size;

    [[nodiscard]] auto all_nodes() const -> std::unordered_set<DawgNode *>;
  };
} // namespace liblevenshtein


namespace std {

  template <>
  struct hash<liblevenshtein::Dawg> {
    auto operator()(const liblevenshtein::Dawg &dawg) const -> size_t;
  };
} // namespace std


#endif // LIBLEVENSHTEIN_COLLECTION_DAWG_H
